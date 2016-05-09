<?php
/**
 * @file for Set default title of term
 */

/**
 * callback from hook_menu()
 */
function _userinfo_create_user_form() {
  drupal_add_css(drupal_get_path('module', 'userinfo') . '/css/userinfo_user_form.css');

  $UserForm = new UserForm();
  $form = $UserForm->createForm();

  $output = $UserForm->formStyle($form);
  return $output;
}

/**
 * callback from hook_menu()
 */
function _userinfo_edit_user_form($uid = NULL) {
  drupal_add_css(drupal_get_path('module', 'userinfo') . '/css/userinfo_user_form.css');

  $UserForm = new UserForm();
  $form = $UserForm->editForm($uid);

  $output = $UserForm->formStyle($form);
  return $output;
}

