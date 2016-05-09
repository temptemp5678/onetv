<?php
/**
 * @file
 */

/**
 * class
   $UserQuery = new UserQuery($nid);
   $UserQuery->userAllList();
 */
class UserQuery {
  /**
   * @return array
   * All User Uid
   */
  public function userAllList($active_user = TRUE) {
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

  /**
   * @param array, Specify Role RID
   * authenticated User 2
   * administrator 3
   *
   * @return array
   *  user Uid list
   */
  public function userAllListByRole($role_id_array = NULL, $active_user = TRUE) {
    $user_uid_array = array();

    if (!$role_id_array) {
      return $role_id_array;
    }

    if (!(count($this->userAllList($active_user)) > 0)) {
      return $user_uid_array;
    }

    // load all user, check if user role is match, if it is true, push to array
    $users = user_load_multiple($this->userAllList($active_user));
    foreach($users as $user) {
      if (array_intersect($role_id_array, array_keys($user->roles))) {
        $user_uid_array[] = $user->uid;
      }
    }

    return $user_uid_array;
  }

}
