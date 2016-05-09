<?php
/**
 * @file
 */

/**
 * class
   $UserInfo = new UserInfo($uid);
   $UserInfo->userName();
 */
class BasicUserInfo {
  public $uid;
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

  /** - - - - - Basic Object - - - - - - - - - -  - - - - -   */
  /**
   * all Methods
   */
  protected function allMethods() {
    $methods = NULL;

    /**
     * similar with  $methods = get_class_methods($this);
     */
    $reflect = new ReflectionClass(get_class($this));
    $methods = $reflect->getMethods(ReflectionProperty::IS_PUBLIC);

    return $methods;
  }

  /**
   * all Methods with filter condition
   */
  protected function allMethodsArray() {
    $output = NULL;

    $methods = $this->allMethods();
    if (is_array($methods)) {
      foreach ($methods as $method) {
        if ($method->name != '__construct') {
          if ($method->name != 'allMethodsValue') {
            $output[] = $method->name;
          }
        }
      }
    }
    return $output;
  }

  /**
   * all Methods value
   * @return, array
     array{
       method1 => value1,
       method2 => value2,
     };
   */
  public function allMethodsValue() {
    $output = array();

    $methods = $this->allMethodsArray();
    if (is_array($methods)) {
      $row = '';
      foreach ($methods as $key => $method) {
        $row[$method] = $this->$method();
      }
      $output = $row;
    }
    return $output;
  }

  /** - - - - - user link  - - - - - - - - - -  - - - - -   */

  /**
   * @return Term Description
   */
  public function userEditLink() {
    $output = NULL;
    if ($this->user) {
      $output = base_path() . 'manage/user/edit/' . $this->user->uid;
    }
    return $output;
  }

  /** - - - - - - basic field value - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return value
   */
  public function fieldSafeValue($field_name = '') {
    $output = NULL;
    if (isset($this->node->{$field_name}['und'][0]['safe_value'])) {
      $output = $this->node->{$field_name}['und'][0]['safe_value'];
    }
    return $output;
  }

  /**
   * @return value
   */
  public function fieldTargetId($field_name = '') {
    $output = NULL;
    if (isset($this->node->{$field_name}['und'][0]['target_id'])) {
      $output = $this->node->{$field_name}['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return value
   */
  public function fieldTargetIdObject($field_name = '') {
    $output = NULL;
    if (isset($this->node->{$field_name}['und'][0]['target_id'])) {

      $TermInfo = new TermInfo($this->node->{$field_name}['und'][0]['target_id']);
      if(!empty($TermInfo)) {
        $output = $TermInfo;
      }
    }
    return $output;
  }

  /**
   * @return value
   */
  public function fieldValue($field_name = '') {
    $output = NULL;
    if (isset($this->node->{$field_name}['und'][0]['value'])) {
      $output = $this->node->{$field_name}['und'][0]['value'];
    }
    return $output;
  }

  /** - - - - - user object - - - - - - - - - -  - - - - -   */
  /**
   * @return integer, Uid
   */
  public function userUid() {
    $output = NULL;
    if (isset($this->user->uid)) {
      $output = $this->user->uid;
    }
    return $output;
  }
  /**
   * @return String, Name
   */
  public function userName() {
    $output = NULL;
    if (isset($this->user->name)) {
      $output = $this->user->name;
    }
    return $output;
  }
  /**
   * @return String, email
   */
  public function userEmail() {
    $output = NULL;
    if (isset($this->user->mail)) {
      $output = $this->user->mail;
    }
    return $output;
  }
  /**
   * @return Array, integer, Roles RID
   */
  public function userRolesRid() {
    $output = NULL;

    if (isset($this->user->roles)) {
      $output = array_keys($this->user->roles);
    }
    return $output;
  }
  /**
   * @return Array, String, Roles Rid => Role Name
   */
  public function userRolesName() {
    $output = NULL;

    if (isset($this->user->roles)) {
      $output = $this->user->roles;
    }
    return $output;
  }

  /** - - - - - user Avatar - - - - - - - - - -  - - - - -   */
  /**
   * @return User avatar
   */
  public function userAvatarImage() {
    $user_avatar = NULL;

    if( isset($this->user->picture->fid) ){
      // load fid
      $file = file_load($this->user->picture->fid);

      if ($file) {
        $image = array(
          'path' => $file->uri,
          'alt' => 'avatar',
          'attributes' => array('class' => 'img-circle'),
          'width' => 48,
          'height' => 48,
        );
        $user_avatar = theme('image', $image);
      }
    }
    return $user_avatar;
  }

}

/**
 * class
   $UserInfo = new UserInfo($tid);
   $UserInfo->phone();
 */
class UserInfo extends BasicUserInfo {

  /** - - - - - user field - - - - - - - - - -  - - - - -   */

  /**
   * @return String, Title
   */
  public function phone() {
    $output = NULL;

    if (isset($this->user->field_user_phone['und'][0]['value'])) {
      $output = $this->user->field_user_phone['und'][0]['value'];
    }
    return $output;
  }

}
