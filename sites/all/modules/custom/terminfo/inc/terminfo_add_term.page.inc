<?php
/**
 * @file for Add new term
 */

/**
 * Implements hook_form(), callback from hook_menu()
 */
function _terminfo_client_add_term() {
  drupal_add_css(drupal_get_path('module', 'terminfo') . '/css/terminfo_add_term.css');

  $form_id = 'taxonomy_form_term';

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $vocabulary = taxonomy_vocabulary_load(3);

  $edit = array();
  $form = drupal_get_form($form_id, $edit, $vocabulary);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  $form['description']['#access'] = FALSE;
  $form['path']['alias']['#access'] = FALSE;
  $form['relations']['#attributes']['class'][] = 'element-hidden';

  $form['actions']['submit']['#prefix'] = '<div class="row text-center clear-both">';
  $form['actions']['submit']['#suffix'] = '</div>';
  $form['actions']['submit']['#attributes']['class'][] = 'margin-top-24';
  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  $output = drupal_render($form);

  return $output;
}

/**
 * Implements hook_form(), callback from hook_menu()
 */
function _terminfo_brand_add_term() {
  drupal_add_css(drupal_get_path('module', 'terminfo') . '/css/terminfo_add_term.css');

  $form_id = 'taxonomy_form_term';

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $vocabulary = taxonomy_vocabulary_load(2);

  $edit = array();
  $form = drupal_get_form($form_id, $edit, $vocabulary);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  $form['description']['#access'] = FALSE;
  $form['path']['alias']['#access'] = FALSE;
  $form['relations']['#attributes']['class'][] = 'element-hidden';

  $form['actions']['submit']['#prefix'] = '<div class="row text-center clear-both">';
  $form['actions']['submit']['#suffix'] = '</div>';
  $form['actions']['submit']['#attributes']['class'][] = 'margin-top-24';
  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  $output = drupal_render($form);

  $terms = taxonomy_get_tree(2);
  $output .= '<div class="margin-top-24">';
    $output .= '<div class="row">';
      foreach ($terms as $key => $value) {
        $output .= '<div class="col-xs-6 col-sm-4 col-md-3 margin-top-24">';
          $output .= '<span class="glyphicon glyphicon-th"></span>';
          $output .= '<span class="margin-left-8">' . $value->name . '</span>';
        $output .= '</div>';
      }
    $output .= '</div>';
  $output .= '</div>';

  return $output;
}
