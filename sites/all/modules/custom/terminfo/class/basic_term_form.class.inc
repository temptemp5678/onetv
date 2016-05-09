<?php
/**
 * @file

 *
 */
/**
 * class
   $TermForm = new TermForm($tid);
   $TermForm->editForm($vid, $tid);
 */
class TermForm {
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
  public function createForm($vid = NULL) {
    if (!$vid) {
      return drupal_not_found();
    }

    $form_id = 'taxonomy_form_term';
    $vocabulary = taxonomy_vocabulary_load($vid);

    drupal_set_title(t('Create') . ' ' . $vocabulary->name);

    $form_state = array();
    $form_state['build_info']['args'] = array($vocabulary);
    form_load_include($form_state, 'inc', 'taxonomy', 'taxonomy.admin');

    $form = drupal_build_form($form_id, $form_state);

    $form['actions']['submit']['#prefix'] = '<div class="row text-center clear-both">';
    $form['actions']['submit']['#suffix'] = '</div>';
    $form['actions']['submit']['#attributes']['class'][] = 'margin-top-24';

    $output = drupal_render($form);
    return $output;
  }

  /** - - - - - Edit  - - - - - - - - - - - - - - - - - - - - - - - - -   */
  /**
   * @return user drupal_render() Renders HTML given a structured array tree.
   */
  public function editForm($vid = NULL, $tid = NULL) {
    $output = NULL;

    $term = taxonomy_term_load($tid);
    if (!$term) {
      return drupal_not_found();
    }
    if ($term->vid != $vid) {
      return drupal_not_found();
    }

    $TermInfo = new TermInfo($tid);
    drupal_set_title(t('Edit') . ' ' . $TermInfo->termVidName());

    $form_id = 'taxonomy_form_term';
    $vocabulary = taxonomy_vocabulary_load($vid);
    $form_state = array();
    $form_state['build_info']['args'] = array($vocabulary);
    $form_state['build_info']['args'] = array($term);
    form_load_include($form_state, 'inc', 'taxonomy', 'taxonomy.admin');
    $form = drupal_build_form($form_id, $form_state);

    $output = drupal_render($form);
    return $output;
  }

}
