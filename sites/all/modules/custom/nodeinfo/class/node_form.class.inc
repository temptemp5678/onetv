<?php
/**
 * @file

 *
 */
/**
 * class
   $NodeForm = new NodeForm();
   $NodeForm->createForm($type);
 */
class NodeForm {
  /**
   * @return, Renders HTML given a structured array tree.
   */
  public function formStyle($form = NULL) {
    $output = '';
    $output .= '<div class="row">';
      $output .= '<div class="col-xs-12 col-sm-12 col-md-10 center-block float-none bg-f6f6f6 padding-0">';
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
   * @return use drupal_render() Renders HTML given a structured array tree.
   */
  public function createForm($type = NULL) {
    if (!$type) {
      return drupal_not_found();
    }

    global $user;

    $form_id = $type . '_node_form';

    $node = (object) array(
      'uid' => $user->uid,
      'name' => (isset($user->name) ? $user->name : ''),
      'type' => $type,
      'language' => LANGUAGE_NONE,
    );

    $form_state['build_info']['args'] = array($node);
    form_load_include($form_state, 'inc', 'node', 'node.pages');
    $form = drupal_build_form($form_id, $form_state);

    $form['revision_information']['#access'] = FALSE;
    $form['author']['#access'] = FALSE;

    $output = drupal_render($form);

    return $output;
  }

  /**
   * @return use drupal_render() Renders HTML given a structured array tree.
   */
  public function editForm($type = NULL, $nid = NULL) {
    if (!$type) {
      return drupal_not_found();
    }

    $node = node_load($nid);
    if (!$node) {
      return drupal_not_found();
    }

    drupal_set_title(t('Edit') . ' ' . $node->title);

    $form_id = $type . '_node_form';
    $form_state['build_info']['args'] = array($node);

    form_load_include($form_state, 'inc', 'node', 'node.pages');
    $form = drupal_build_form($form_id, $form_state);

    $form['revision_information']['#access'] = FALSE;
    $form['author']['#access'] = FALSE;

    // Add customize checkbox
    $form['custom_published'] = $form['options']['status'];
    $form['custom_published']['#weight'] = 100;
    $form['custom_published']['#prefix'] = '<div class="custom-published-wrapper">';
    $form['custom_published']['#suffix'] = '</div>';

    drupal_add_js(drupal_get_path('module', 'nodeinfo') .'/js/ajax_custom_published_toggle.js');
    $output = drupal_render($form);

    return $output;
  }

  /**
   * @return use drupal_render() Renders HTML given a structured array tree.
   */
  public function duplicateForm($type = NULL, $nid = NULL) {
    if (!$type) {
      return drupal_not_found();
    }

    $node = node_load($nid);
    if (!$node) {
      return drupal_not_found();
    }

    global $user;
    $form_id = $type . '_node_form';

    $new_node = (object) array(
      'uid' => $user->uid,
      'name' => (isset($user->name) ? $user->name : ''),
      'type' => $type,
      'language' => LANGUAGE_NONE,
    );

    foreach ($node as $key => $value) {
      if (strpos($key, 'field_quote_') !== false) {
        $new_node->{$key} = $node->{$key};
      }
    }

    // reference_quote
    if (!isset($node->field_quote_reference_quote['und'][0]['target_id'])) {
      $new_node->field_quote_reference_quote['und'][0]['target_id'] = $nid;
    }

    drupal_set_title(t('Duplicate') . ' ' . $node->title);

    $form_id = $type . '_node_form';
    $form_state['build_info']['args'] = array($new_node);

    form_load_include($form_state, 'inc', 'node', 'node.pages');
    $form = drupal_build_form($form_id, $form_state);

    $form['revision_information']['#access'] = FALSE;
    $form['author']['#access'] = FALSE;

    $output = drupal_render($form);

    return $output;
  }
}
