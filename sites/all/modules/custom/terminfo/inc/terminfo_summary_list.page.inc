<?php
/**
 * @file for New Client Form
 */

/**
 * Implements page_callback(), callback from hook_menu()
 * embed a dash table to show table
 */
function _terminfo_client_index_list() {
  /**
   * load js
   */
  drupal_add_js(drupal_get_path('module', 'terminfo') .'/ng_js/terminfo_summary_client.js');
  drupal_add_css(drupal_get_path('module', 'terminfo') .'/css/terminfo_summary_client.css');

  /**
   * output
   */
  $output = '';
  $output .= '<div data-ng-app="termClientIndex" class="row margin-0">';

    $output .= '<div data-ng-cloak>';
      $output .= '<md-content>';
        $output .= '<md-tabs md-dynamic-height md-border-bottom>';
          $output .= '<md-tab label="' . t('Client') . '">';
            $output .= '<md-content class="md-padding">';
              $output .= _terminfo_client_list_table();
            $output .= '</md-content>';
          $output .= '</md-tab>';
          $output .= '<md-tab label="' . t('Contact') . '">';
            $output .= '<md-content class="md-padding">';
              $output .= _terminfo_contact_list_table();
            $output .= '</md-content>';
          $output .= '</md-tab>';
        $output .= '</md-tabs>';
      $output .= '</md-content>';
    $output .= '</div>';

  $output .= '</div>';

  return $output;
}

/**
 * Implements page_callback(), callback from hook_menu()
 * embed a dash table to show table
 */
function _terminfo_client_list_table() {
  $output = '';
  $output .= '<div data-ng-controller="termClientController" class="row margin-0">';

    /**
     * filter
     */
    $output .= '<div class=" margin-top-6">';
      $output .= '<span class="float-left">';
        $output .= t('Search') . ' <input data-ng-model="inputFilter.$">';
      $output .= '</span>';
    $output .= '</div>';

    $output .= '<div class="float-right fa-toggle-wrapper">';
      $output .= '<span class="font-size-30">';
        $output .= '<i class="fa fa-toggle-on active" data-ng-if="clientToggleStatus == true" data-ng-click="clientToggleStatusChange();"></i>';
        $output .= '<i class="fa fa-toggle-on fa-rotate-180 inactive" data-ng-if="clientToggleStatus == false" data-ng-click="clientToggleStatusChange();"></i>';
      $output .= '</span>';
      $output .= '<span class="font-size-12 margin-left-6 position-relative top-n-6" data-ng-if="clientToggleStatus == true">';
        $output .= t('All Client');
      $output .= '</span>';
      $output .= '<span class="font-size-12 margin-left-6 position-relative top-n-6" data-ng-if="clientToggleStatus == false">';
        $output .= t('My Client');
      $output .= '</span>';
    $output .= '</div>';

    $output .= '<div class="float-right margin-top-6 margin-right-24">';
      $output .= '<button class="btn btn-default">';
        $output .= l(t('Add Client'), 'manage/client/add', array(
            'attributes' => array('class' => array('text-center')),
            'query' => array('destination' => 'term/client/index'),
          ));
      $output .= '</button>';
    $output .= '</div>';

    /**
     * data table
     */
    $output .= '<div class="margin-top-12">';
      $output .= '<table class="table table-hover">';
        $output .= '<thead>';
          $output .= '<tr>';
            $output .= '<th><a href="" data-ng-click="sortField = \'client_name\' ; reverse= !reverse ">' . t('Client') . '</a></th>';
            $output .= '<th><a href="" data-ng-click="sortField = \'province\' ; reverse= !reverse ">' . t('Province') . '</a></th>';
            $output .= '<th></th>';
            $output .= '<th></th>';
            $output .= '<th></th>';
          $output .= '</tr>';
        $output .= '</thead>';

        $output .= '<tbody data-ng-repeat="row in sourcedata | filter:inputFilter | orderBy:sortField:reverse " class="">';
          $output .= '<tr data-ng-show="!currentClientStatus(row.clientManageUserArray) || clientToggleStatus">';
            $output .= '<td>{{ row.termName }}</td>';
            $output .= '<td>{{ row.provinceName }}</td>';
            $output .= '<td><a href="{{ row.link }}"><i class="fa fa-external-link fa-lg"></i></a></td>';
            $output .= '<td><a href="{{ row.termEditLink }}"><i class="fa fa-pencil-square-o fa-lg color-767676"></i></a></td>';
            $output .= '<td data-ng-show="clientToggleStatus"><a href="{{ row.linkAddUserClientManager }}" data-ng-show="currentClientStatus(row.clientManageUserArray)"><i class="fa fa-plus fa-lg"></i></a></td>';
            $output .= '<td data-ng-show="!clientToggleStatus"><a href="{{ row.linkRemoveUserClientManager }}" data-ng-hide="currentClientStatus(row.clientManageUserArray)"><i class="fa fa-times fa-lg color-f26411"></i></a></td>';
          $output .= '</tr>';

          $output .= '<tr>';
            $output .= '<td colspan="100%" data-ng-show="hoverEdit">{{ row.description }}</td>';
          $output .= '</tr>';

        $output .= '</tbody>';
      $output .= '</table>';
    $output .= '</div>';
  $output .= '</div>';


  return $output;
}

/**
 * Implements page_callback(), callback from hook_menu()
 */
function _terminfo_contact_list_table() {
  $output = '';
  $output .= '<div data-ng-controller="termContactController" class="row margin-0">';

    /**
     * filter
     */
    $output .= '<div class="margin-top-6">';
      $output .= '<span class="float-left">';
        $output .= t('Search') . ' <input data-ng-model="inputFilter.$">';
      $output .= '</span>';
    $output .= '</div>';

    $output .= '<div class="float-right margin-right-24">';
      $output .= '<button class="btn btn-default">';
        $output .= l(t('Add Contact'), 'manage/contact/add', array(
            'attributes' => array('class' => array('text-center')),
            'query' => array('destination' => 'term/client/index'),
          ));
      $output .= '</button>';
    $output .= '</div>';

    /**
     * data table
     */
    $output .= '<div class="margin-top-12">';
      $output .= '<table class="table table-hover">';
        $output .= '<thead>';
          $output .= '<tr>';
            $output .= '<th>' . t('Contact') . '</a></th>';
            $output .= '<th>' . t('Client') . '</a></th>';
            $output .= '<th>' . t('Phone') . '</a></th>';
            $output .= '<th>' . t('Mobile') . '</a></th>';
            $output .= '<th></th>';
            $output .= '<th></th>';
          $output .= '</tr>';
        $output .= '</thead>';

        $output .= '<tbody data-ng-repeat="row in sourcedata | filter:inputFilter">';
          $output .= '<tr>';
            $output .= '<td>{{ row.termName }}</td>';
            $output .= '<td>{{ row.clientName }}</td>';
            $output .= '<td>{{ row.phone }}</td>';
            $output .= '<td>{{ row.mobile }}</td>';
            $output .= '<td><a href="{{ row.link }}"><i class="fa fa-external-link fa-lg"></i></a></td>';
            $output .= '<td><a href="{{ row.termEditLink }}"><i class="fa fa-pencil-square-o fa-lg color-767676"></i></a></td>';
          $output .= '</tr>';
        $output .= '</tbody>';
      $output .= '</table>';
    $output .= '</div>';

  $output .= '</div>';

  return $output;
}
