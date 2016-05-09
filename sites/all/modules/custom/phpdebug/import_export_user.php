<?php

function userAllList($active_user = TRUE) {
  // not use "entity_load('user')" to load all user, because it need add condition for "$active_user"

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user');
  if ($active_user) {
    $query->propertyCondition('status', 1);
  }
  $result = $query->execute();

  if (isset($result['user'])) {
    if (count($result['user']) > 0 ) {
      $users_uid_array = array_keys($result['user']);
    }
  }
  return $users_uid_array;
}

$all_uids = userAllList();

$output = array();
if (is_array($all_uids)) {
  foreach ($all_uids as $key => $value) {
    $UserInfo = new UserInfo($value);

    $row = '';
    if ($UserInfo->userUid() > 1) {
      $row = array(
        '"' . $UserInfo->userName() . '"',
        '"' . $UserInfo->userEmail(). '"',
        '"' . $UserInfo->firstName(). '"',
        '"' . $UserInfo->lastName(). '"',
        '"' . $UserInfo->provinceName(). '"',
      );

      print_r('array(' . implode(',', $row) . '),');
    }
  }
}
/** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
// define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

require('includes/password.inc');

$get_users = userArray();

foreach($get_users as $key => $value){

  // Define specific role IDs for the user.
  $roles = array(2, 8,);

  // Get an empty object with the is_new attribute set to TRUE.
  $user = entity_create('user', array());
  $user->name = $value[0];
  // Enable the user by default.
  $user->status = 1;
  // Set nescessary role to let the user log in.
  $user->roles = drupal_map_assoc($roles + array(DRUPAL_AUTHENTICATED_RID));
  // Set e-mail for lost password procedure.
  $user->init = $value[1];
  $user->mail = $value[1];
  // Set hashed password.
  $user->pass = user_hash_password('password');

  // Once we have enough data, set the wrapper around the user object.
  $user = entity_metadata_wrapper('user', $user);

  // Save the user.
  $user->save();
}

/**
 * import citys data
 */
function userArray() {
  $users = array(
    array("testrep","testrep22@flexxia.ca","",""),
  );

  return $users;
}
