<?php
/**
 * @file
 */

/**
 * class
   $UserAction = new UserAction($para);
   $UserAction->updateUserData();
 */
class UserAction {
  protected $uid;
  public $user = NULL;

  /**
   * @parameter is uid
   */
  function __construct($param){
    if (is_numeric($param)) {
      $user = user_load($param);
      if ($user) {
        $this->user = $user;
        $this->uid = $param;
      }
    }
    else if (is_object($param)) {
      if (isset($param->uid)) {
        $user = user_load($param->uid);
        if ($user) {
          $this->user = $user;
          $this->uid = $this->user->uid;
        }
      }
    }
  }

  /** - - - - - - action - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  /**
   * @param, data key and value
   */
  public function updateUserData($key = NULL, $value = NULL) {
    if ($this->user) {
      if (isset($key)) {
        $edit = $this->user->data;
        $edit['data'][$key] = $value;

        user_save($this->user, $edit);
      }
    }
  }

}
