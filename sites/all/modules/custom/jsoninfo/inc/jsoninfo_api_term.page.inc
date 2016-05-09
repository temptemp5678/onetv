<?php
/**
 * callback from hook_menu()
 */
function _jsoninfo_term_all_program_data() {
  $SourceJson = new SourceJson();
  drupal_json_output($SourceJson->allProgramData());
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_term_business_unit_edit($tid = NULL) {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonTermBusinessUnitEdit($tid));
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_term_evaluation_form_edit($tid = NULL) {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonTermEvaluationFormEdit($tid));
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_term_evaluation_form_list() {
  $SourceJson = new SourceJson();
  drupal_json_output($SourceJson->allEvaluationForm());
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_term_evaluation_form_question_set($tid = NULL) {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonTermEvaluationFormQuestionSet($tid));
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_term_evaluation_form_question_list() {
  $SourceJson = new SourceJson();
  drupal_json_output($SourceJson->evaluationFormQuestionList());
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_term_program_edit($tid = NULL) {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonTermProgramEdit($tid));
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_term_program_list() {
  $SourceJson = new SourceJson();
  drupal_json_output($SourceJson->termProgramList());
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_term_question_field_create() {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->termQuestionFieldCreate());
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_term_question_field_data() {
  $SourceJson = new SourceJson();
  drupal_json_output($SourceJson->allQuestionField());
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_term_question_library() {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->termQuestionLibrary());
}
/**
 * callback from hook_menu()
 */
function _jsoninfo_term_question_library_edit($tid = NULL) {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonTermQuestionLibraryEdit($tid));
}
/**
 * callback from hook_menu()
 */
function _jsoninfo_term_question_library_list() {
  $SourceJson = new SourceJson();
  drupal_json_output($SourceJson->questionLibraryList());
}
/**
 * callback from hook_menu()
 */
function _jsoninfo_term_question_library_field_option() {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonTermQuestionLibraryFieldOption());
}
/**
 * callback from hook_menu()
 */
function _jsoninfo_term_question_library_table() {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonTermQuestionLibraryTable());
}
