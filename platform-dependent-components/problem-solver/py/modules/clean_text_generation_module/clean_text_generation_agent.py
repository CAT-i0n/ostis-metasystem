import logging

import g4f
from g4f.client import Client
from requests import HTTPError
from sc_client.client import template_search
from sc_client.constants import sc_types
from sc_client.models import ScAddr, ScLinkContentType, ScTemplate
from sc_kpm import ScAgentClassic
from sc_kpm.sc_keynodes import Idtf
from sc_kpm.sc_result import ScResult
from sc_kpm.utils import create_link, get_link_content_data, get_system_idtf
from sc_kpm.utils.action_utils import (create_action_answer,
                                       finish_action_with_status,
                                       get_action_arguments)

from . import constants

logging.basicConfig(
    level=logging.INFO, format="%(asctime)s | %(levelname)s | %(name)s | %(message)s", datefmt="[%d-%b-%y %H:%M:%S]"
)


class CleanTextGenerationAgent(ScAgentClassic):
    def __init__(self) -> None:                     
        super().__init__(constants.ACTION_GET_CLEAN_TEXT)    

    def on_event(self, event_element: ScAddr, event_edge: ScAddr, action_element: ScAddr) -> ScResult:
        result = self.run(action_element)
        is_successfull = result == ScResult.OK
        finish_action_with_status(action_element, is_successfull)
        self.logger.info(
            "CleanTextGenerationAgent finished %s", "successfully" if is_successfull else "unsuccessfully"
        )
        return result           

    def run(self, action_element: ScAddr) -> ScResult:
        self.logger.info('CleanTextGenerationAgent started')      
        # Get sc-link with raw text        
        raw_text_node = get_action_arguments(action_element, 1)[0]
        if not raw_text_node:
            self.logger.error('CleanTextGenerationAgent: could not find raw text sc-link to process')
            return ScResult.ERROR_INVALID_PARAMS
        
        #Get language of raw text sc-link
        language_template = ScTemplate()
        language_template.triple(
            sc_types.NODE_CLASS >> "language",
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            raw_text_node
        )
        search_result = template_search(language_template)
        if not len(search_result):
            self.logger.error('CleanTextGenerationAgent: language link not found.')
            return ScResult.ERROR_INVALID_PARAMS
        language_node = search_result[0][language]
        language = get_system_idtf(language_node)
        if not language in constants.AVAILABLE_LANGUAGES:
            self.logger.error(f'CleanTextGenerationAgent: unknown language')
            return ScResult.ERROR_INVALID_PARAMS
        
        # Get raw text string
        raw_text = get_link_content_data(raw_text_node)        
        if not isinstance(raw_text, str):
            self.logger.error(f'CleanTextGenerationAgent: invalid link content')
            return ScResult.ERROR_INVALID_TYPE
        

        if not raw_text:
            self.logger.error(f'CleanTextGenerationAgent: input link is empty')
            return ScResult.ERROR_INVALID_PARAMS

        clean_text = self._get_clean_text(raw_text, language)            
        
        # Check text for emptiness. If processed text is empty, that means that model does not work
        if clean_text is None or clean_text == '':
            self.logger.error(f'CleanTextGenerationAgent: error with text processing')
            return ScResult.ERROR

        answer_link = create_link(clean_text, ScLinkContentType.STRING)        
        create_action_answer(action_element, answer_link)
        finish_action_with_status(action_element, True)
        return ScResult.OK
    
    def _get_clean_text(self, raw_text: str, language: str) -> str:
        client = Client()
        messages = [{'role': 'user', 'content': constants.PROMPTS[language].format(raw_text)}]
        response = client.chat.completions.create(
            model='gpt-3.5-turbo',
            messages=messages,
            temperature=0,
        )
        self.logger.info(f'Successfully cleaned text for you\n: {response}')
        self.logger.info(response.choices[0].message.content)
        return response.choices[0].message.content      
