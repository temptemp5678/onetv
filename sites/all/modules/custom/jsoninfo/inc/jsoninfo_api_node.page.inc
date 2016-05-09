<?php
/**
 * callback from hook_menu()
 */
function _jsoninfo_node_event_list($tid = NULL, $start_time = NULL, $end_time = NULL) {
  $TermProgramQuery = new TermProgramQuery();
  $program_tids = $TermProgramQuery->programTidsByUnit($tid);

  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonNodeEventList($program_tids, $start_time, $end_time));
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_node_evaluation_question_set($meeting_nid = NULL) {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonNodeEvaluationFormQuestionSet($meeting_nid));
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_node_meeting_create() {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->nodeMeetingCreate());
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_node_meeting_edit($nid = NULL) {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonNodeMeetingEdit($nid));
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_node_meeting_list() {
  $SourceJson = new SourceJson();
  drupal_json_output($SourceJson->nodeMeetingList());
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_node_meeting_map($tid = NULL, $start_time = NULL, $end_time = NULL) {
  $TermProgramQuery = new TermProgramQuery();
  $program_tids = $TermProgramQuery->programTidsByUnit($tid);

  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonPageMeetingMap($program_tids, $start_time, $end_time));
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_node_meeting_detail($nid = NULL) {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonNodeMeetingDetail($nid));
}
