<?php
/**
 * @file for Set default title of term
 */

/**
 * callback from hook_menu()
 */
function _userinfo_user_list() {
  /**
   * load js
   */
  drupal_add_js(drupal_get_path('module', 'userinfo') .'/ng_js/userinfo_list_data.ng.js');

  $output = '';
  $output .= '<div data-ng-app="userListData" class="row margin-0">';
    $output .= '<div data-ng-controller="UserListController" class="row margin-0">';

      /**
       * data table
       */
      $output .= '<div class="margin-top-12">';
        $output .= '<table class="table table-hover">';
          $output .= '<thead>';
            $output .= '<tr>';
              $output .= '<th>' . t('Name') . '</a></th>';
              $output .= '<th>' . t('Phone') . '</a></th>';
              $output .= '<th>' . t('Mobile') . '</a></th>';
              $output .= '<th></th>';
            $output .= '</tr>';
          $output .= '</thead>';

          $output .= '<tbody data-ng-repeat="row in sourcedata">';
            $output .= '<tr>';
              $output .= '<td>{{ row.userName }}</td>';
              $output .= '<td>{{ row.phone }}</td>';
              $output .= '<td>{{ row.mobile }}</td>';
              $output .= '<td><a href="{{ row.userEditLink }}?destination=manage/user/list"><i class="fa fa-pencil-square-o fa-lg color-767676"></i></a></td>';
            $output .= '</tr>';
          $output .= '</tbody>';
        $output .= '</table>';
      $output .= '</div>';

    $output .= '</div>';
  $output .= '</div>';

  return $output;
}
