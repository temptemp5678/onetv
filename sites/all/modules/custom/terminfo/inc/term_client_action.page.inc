<?php
/**
 * @file
 */

/**
 * Implements hook_form(), callback from hook_menu()
 */
function _term_client_action_add_client_manager($tid = NULL, $uid = NULL) {
  if (isset($tid) && isset($uid)) {
  }
  else {
    return drupal_not_found();
  }

  $TermClientAction = new TermClientAction($tid);
  $TermClientAction->addClientManageUser($uid);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  // $output = NULL;

  $output = t('Add client successfully');

  if (drupal_valid_path('term/client/index')) {
    // url exists
    drupal_goto('term/client/index');
  }

  return $output;
}

/**
 * Implements hook_form(), callback from hook_menu()
 */
function _term_client_action_remove_client_manager($tid = NULL, $uid = NULL) {
  if (isset($tid) && isset($uid)) {
  }
  else {
    return drupal_not_found();
  }

  $TermClientAction = new TermClientAction($tid);
  $TermClientAction->removeClientManageUser($uid);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  $output = NULL;

  $output = t('Remove client successfully');

  if (drupal_valid_path('term/client/index')) {
    // url exists
    drupal_goto('term/client/index');
  }

  return $output;
}
