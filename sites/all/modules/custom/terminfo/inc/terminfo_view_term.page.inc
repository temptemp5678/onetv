<?php
/**
 * @file for Add new term
 */

/**
 * Implements hook_form(), callback from hook_menu()
 */
function _termInfo_client_view_term($tid = NULL) {
  $TermClientInfo = new TermClientInfo($tid);
  if (!$TermClientInfo->termTid()) {
    return drupal_not_found();
  }

  drupal_set_title($TermClientInfo->termName());
  $term = taxonomy_term_load($tid);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  $output = NULL;

  $output .= '<div class="row margin-0">';
    $output .= '<div class="margin-top-12">';
      $output .= '<fieldset class="panel panel-default form-wrapper">';
        $output .= '<legend class="panel-heading">';
          $output .= '<div class="panel-title fieldset-legend">';
            $output .= t('Client details');
          $output .= '</div>';
        $output .= ' </legend>';
        $output .= ' <div class="panel-body">';
          $output .= '<dl>';
            $output .= '<dt>' . t('Name') . '</dt>';
            $output .= '<dd>' . $TermClientInfo->termName() . '</dd>';
            if ($TermClientInfo->provinceName()) {
              $output .= '<dt>' . t('Province') . '</dt>';
              $output .= '<dd>' . $TermClientInfo->provinceName(). '</dd>';
            }
            if ($TermClientInfo->provinceName()) {
              $output .= '<dt>' . t('Address') . '</dt>';
              $output .= '<dd>' . $TermClientInfo->address(). '</dd>';
            }
            if ($TermClientInfo->postcode()) {
              $output .= '<dt>' . t('Postcode') . '</dt>';
              $output .= '<dd>' . $TermClientInfo->postcode(). '</dd>';
            }
          $output .= '</dl>';
        $output .= '</div>';
      $output .= ' </fieldset>';
    $output .= '</div>';

  $output .= '</div>';

  return $output;
}
