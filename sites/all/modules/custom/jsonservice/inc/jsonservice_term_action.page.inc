<?php

/**
 * Implements page_callback(), callback from hook_menu()
 */
function _jsonservice_term_create($vid = NULL) {
  /**
   * Validate the request is a post and return proper response code on failure.
   */
  // if ($_SERVER['REQUEST_METHOD'] != 'POST'){
  //   header('HTTP/1.1 405 Not Post');
  // }
  /**
   * Authenticate the user, or key and return proper response code on failure.
   */
  // elseif ($_SERVER['PHP_AUTH_USER'] != 'trusted user') {
  //   header('HTTP/1.1 401 Not Authorized');
  // }

  /**
   * When data type and field validation fails return a 204.
   * validating on a key to validate the user permission
   */
  // elseif ($validation == FALSE) {
  //   header('HTTP/1.1 204 Incorrect Data');
  // }
  // watchdog('nodeinfo', 'get json from js');

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * to obtain stream inputs by using file_get_contents
   */
  $received_json = file_get_contents("php://input",  TRUE);
  $json_fields = drupal_json_decode($received_json, TRUE);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  if ($vid) {
    $TermJsonAction = new TermJsonAction();
    $TermJsonAction->insertTerm($vid, $json_fields);

    watchdog('jsonservice', 'Create Term from _jsonservice_term_create()');
  }

  $output = 'Created Term';
  return $output;

  /**
   * After completing the payload a notice of success to inform the application it’s POST was a success.
   * Set header to indicate the item was saved.
   */
  // header('HTTP/1.1 201 Created');
}

/**
 * Implements page_callback(), callback from hook_menu()
 */
function _jsonservice_term_update($tid = NULL) {
  /**
   * to obtain stream inputs by using file_get_contents
   */
  $received_json = file_get_contents("php://input",  TRUE);
  $json_fields = drupal_json_decode($received_json, TRUE);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  if ($tid) {
    $TermJsonAction = new TermJsonAction();
    $TermJsonAction->updateFields($tid, $json_fields);

    watchdog('jsonservice', 'Update Term from _jsonservice_term_update()');
  }

  $output = 'Update Term';
  return $output;
}

/**
 * Implements page_callback(), callback from hook_menu()
 */
function _jsonservice_term_delete($tid = NULL) {
  if ($tid) {
    $TermJsonAction = new TermJsonAction();
    $TermJsonAction->deleteTerm($tid);

    watchdog('jsonservice', 'Delete Term from _jsonservice_term_delete()');
  }

  $output = 'Delete Term';
  return $output;
}

