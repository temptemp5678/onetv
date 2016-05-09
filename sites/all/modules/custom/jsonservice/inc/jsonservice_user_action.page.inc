<?php

/**
 * Implements page_callback(), callback from hook_menu()
 */
function _jsonservice_user_admin_menu($action = FALSE) {
  global $user;

  $output = 'Admin Menu';

  if (isset($user)) {
    // enable or disable admin menu
    if ($action == 'enable') {
      $edit = array(
        'data' => array(
          'navinfo_user_admin_menu_status' => TRUE,
        ),
      );
      $output = 'Admin Menu Enable';
    }
    else {
      $edit = array(
        'data' => array(
          'navinfo_user_admin_menu_status' => FALSE,
        ),
      );
      $output = 'Admin Menu Disable';
    }
    user_save($user, $edit);
  }

  $site_frontpage = variable_get('site_frontpage', '<front>');
  drupal_goto($site_frontpage);
  return $output;
}

/**
 * Implements page_callback(), callback from hook_menu()
 */
function _jsonservice_user_set_date_range($start_time = NULL, $end_time = NULL) {
  $DateTimeClass = new DateTimeClass();
  $DateTimeClass->user_set_date_range($start_time, $end_time);

  $output = 'Set Date Range';
  return $output;
}

/**
 * Implements page_callback(), callback from hook_menu()
 */
function _jsonservice_user_update($uid = NULL) {
  /**
   * to obtain stream inputs by using file_get_contents
   */
  $received_json = file_get_contents("php://input",  TRUE);
  $json_fields = drupal_json_decode($received_json, TRUE);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  $user = user_load($uid);
  if ($user) {
    $UserJsonAction = new UserJsonAction();
    $UserJsonAction->updateFields($uid, $json_fields);

    watchdog('jsonservice', 'Update User from _jsonservice_user_update()');
  }

  $output = 'Update User';
  return $output;
}

