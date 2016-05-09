<?php
/**
 * @file
 */

/**
 * class
 $UserJsonAction = new UserJsonAction();
 $UserJsonAction->updateFields($uid, $json_fields);
 */
class UserJsonAction {

  /** Update field  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /**
   * Update field
   */
  public function updateFields($uid = NULL, $fields = array()) {
    $account = user_load($uid);

    if ($account) {
      $edit = array();

      // custom fields
      foreach ($fields as $field_name => $row) {
        if ($field_name == 'pass') {
          $edit['pass'] = $row;
          continue;
        }
        if ($field_name == 'mail') {
          $edit['mail'] = $row;
          continue;
        }

        $field_info = field_info_field($field_name);
        if ($field_info) {
          $field_type = $field_info['type'];

          switch ($field_type) {
            case 'datestamp':
            case 'list_integer':
            case 'number_integer':
            case 'text':
            case 'text_long':
              $edit[$field_name]['und'] = array();        // set empty firstly
              if (isset($row['und'])) {
                foreach ($row['und'] as $key => $value) {
                  $edit[$field_name]['und'][$key]['value'] = $value;
                }
              }
              break;
            case 'entityreference':
              $edit[$field_name]['und'] = array();        // set empty firstly

              if (isset($row['und'])) {
                foreach ($row['und'] as $key => $value) {
                  $edit[$field_name]['und'][$key]['target_id'] = $value;
                }
              }
              break;

            default:
              break;
          }
        }
      }
      // It's good to call field_attach_presave()
      user_save($account, $edit);
    }
  }

}
