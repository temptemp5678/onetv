<?php
/**
 * callback from hook_menu()
 */
function _terminfo_basic_edit_term($tid = NULL) {
  $TermInfo = new TermInfo($tid);
  if (!$TermInfo->termTid()) {
    return drupal_not_found();
  }

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');

  $form_id = 'taxonomy_form_term';
  $term = taxonomy_term_load($tid);

  $title = t('Edit Term') . ' -- ';
  $title .= $TermInfo->vocabularyName();
  drupal_set_title($title);

  $form = drupal_get_form($form_id, $term);

  /** - - - - - Basic Property - - - - - - - - - -  - - - - -   */
  global $user;
  if (!in_array('administrator', $user->roles)) {
    $form['description']['#access'] = FALSE;
    $form['relations']['#attributes']['class'][] = 'element-hidden';
    $form['path']['#access'] = FALSE;
    $form['path']['alias']['#access'] = FALSE;
    $form['xmlsitemap']['#access'] = FALSE;
  }

  $output = drupal_render($form);

  return $output;
}
