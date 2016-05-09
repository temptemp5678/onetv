<?php

/**
 * callback from hook_menu()
 */
function _jsoninfo_user_list() {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonUserList());
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_user_profile($uid = NULL) {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonUserProfile($uid));
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_user_speaker_details($uid = NULL) {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonUserSpeakerDetails($uid));
}
