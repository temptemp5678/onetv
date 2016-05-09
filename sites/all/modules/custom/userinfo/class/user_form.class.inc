<?php
/**
 * @file

 *
 */
/**
 * class
   $UserForm = new UserForm();
   $UserForm->editForm($uid);
 */
class UserForm {
  /**
   * @return, Renders HTML given a structured array tree.
   */
  public function formStyle0($form = NULL) {
    $output = '';
    $output .= '<div class="row">';
      $output .= '<div class="col-xs-12 col-sm-10 col-md-6 center-block float-none">';
        $output .= '<div class="center-block">';
          $output .= $form;
        $output .= '<div>';
      $output .= '<div>';
    $output .= '<div>';

    return $output;
  }
  /**
   * @return, Renders HTML given a structured array tree.
   */
  public function formStyle($form = NULL) {
    $output = '';
    $output .= '<div class="row">';
      $output .= '<div class="col-xs-12 col-sm-10 col-md-8 center-block float-none bg-f6f6f6 padding-0">';
        $output .= '<div class="center-block">';
          $output .= '<div class="padding-24">';
            $output .= '<div class="bg-ffffff min-height-480">';
              $output .= '<div class="padding-24">';
                $output .= $form;
              $output .= '<div>';
            $output .= '<div>';
          $output .= '<div>';
        $output .= '<div>';
      $output .= '<div>';
    $output .= '<div>';

    return $output;
  }
  /**
   * @return, Renders HTML given a structured array tree.
   */
  public function formStyleOne($form = NULL) {
    $output = '';
    $output .= '<div class="row">';
      $output .= '<div class="col-xs-12 col-sm-10 col-md-10 center-block float-none bg-f6f6f6 padding-0">';
        $output .= '<div class="center-block">';
          $output .= '<div class="padding-24">';
            $output .= '<div class="bg-ffffff min-height-480">';
              $output .= '<div class="padding-24">';
                $output .= $form;
              $output .= '<div>';
            $output .= '<div>';
          $output .= '<div>';
        $output .= '<div>';
      $output .= '<div>';
    $output .= '<div>';

    return $output;
  }

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  /**
   * @return user drupal_render() Renders HTML given a structured array tree.
   */
  public function createForm() {
    drupal_set_title(t('Create User From'));

    global $user;

    $form_id = 'user_register_form';

    $form_state = array();
    $form_state['build_info']['args'] = array($user);

    // Load user.pages.inc and ensure it is automatically reloaded if
    // this form is rebuilt via AJAX or other means.
    form_load_include($form_state, 'inc', 'user', 'user.pages');

    $form = drupal_build_form($form_id, $form_state);

    $output = drupal_render($form);
    return $output;
  }

  /** - - - - - Edit  - - - - - - - - - - - - - - - - - - - - - - - - -   */
  /**
   * @return user drupal_render() Renders HTML given a structured array tree.
   */
  public function editForm($uid = NULL) {
    $output = NULL;

    if (!is_numeric($uid)) {
      return drupal_not_found();
    }

    $user = user_load($uid);
    if ( !($user && ($user->uid > 1)) ) {
      return drupal_not_found();
    }

    $form_id = 'user_profile_form';

    $form_state = array();
    $form_state['build_info']['args'] = array($user);

    // Load user.pages.inc and ensure it is automatically reloaded if
    // this form is rebuilt via AJAX or other means.
    form_load_include($form_state, 'inc', 'user', 'user.pages');

    $form = drupal_build_form($form_id, $form_state);
    $output = drupal_render($form);

    return $output;
  }

}
