<?php

/**
 * Implements page_callback(), callback from hook_menu()
 */
function _jsonservice_node_answerset_create($node_type = NULL) {
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
  if ($node_type) {
    $NodeJsonAnswersetAction = new NodeJsonAnswersetAction($node_type);
    $NodeJsonAnswersetAction->insertNodeFields($json_fields);
  }
  $output = 'Created Node';

  watchdog('jsonservice', 'Create node answerset from _nodeinfo_json_create()');

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
function _jsonservice_node_answerset_update($nid = NULL) {
  /**
   * to obtain stream inputs by using file_get_contents
   */
  $received_json = file_get_contents("php://input",  TRUE);
  $json_fields = drupal_json_decode($received_json, TRUE);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  if ($nid) {
    $node_type = '';
    $node = node_load($nid);
    if ($node) {
      $node_type = $node->type;
    }

    $NodeJsonAnswersetAction = new NodeJsonAnswersetAction($node_type);
    $NodeJsonAnswersetAction->updateFields($nid, $json_fields);

  }
  $output = 'Update Node';

  watchdog('jsonservice', 'Update node answerset from _nodeinfo_json_update()');

  return $output;
}

