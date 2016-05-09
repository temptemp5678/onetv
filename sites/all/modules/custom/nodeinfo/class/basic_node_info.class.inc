<?php
/**
 * @file
 */

/**
 * class
   $NodeInfo = new NodeInfo($nid);
   $NodeInfo->nodeTitle();
 */
class NodeInfo {
  public $nid;
  public $node = NULL;

  /**
   * @parameter is nid or node object
   */
  function __construct($para){
    if (is_numeric($para)) {
      $node = node_load($para);
      if ($node) {
        $this->node = $node;
        $this->nid = $this->node->nid;
      }
    }
    else if (is_object($para)) {
      if (isset($para->nid)) {
        $this->node = $para;
        $this->nid = $this->node->nid;
      }
    }
  }
  /** - - - - - - field - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  // public function entityWrapper() {
  //   $output = NULL;
  //   if (isset($this->node->nid)) {
  //     $output = entity_metadata_wrapper('node', $this->node);
  //   }
  //   return $output;
  // }
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

  /** - - - - - Basic Property - - - - - - - - - -  - - - - -   */

  /**
   * @return String, Node Title
   */
  public function nodeNid() {
    $output = NULL;
    if (isset($this->nid)) {
      $output = $this->nid;
    }
    return $output;
  }

  /**
   * @return String, Node Title
   */
  public function nodeTitle() {
    $output = NULL;
    if (isset($this->node->title)) {
      $output = $this->node->title;
    }
    return $output;
  }

  /**
   * @return String, Node Title
   */
  public function nodeBody() {
    $output = NULL;
    if (isset($this->node->body['und'][0]['value'])) {
      $output = $this->node->body['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return String, Node Title
   */
  public function nodeUid() {
    $output = $this->node->uid;
    return $output;
  }
  /**
   * @return String,
   */
  public function nodeUidName() {
    $output = '';
    $UserInfo = new UserInfo($this->nodeUid());
    $output = $UserInfo->userName();

    return $output;
  }

  /**
   * @return String, Node type
   */
  public function nodeType() {
    $output = NULL;
    if (isset($this->node->type)) {
      $output = $this->node->type;
    }
    return $output;
  }

  /**
   * @return String,
   */
  public function status() {
    $output = NULL;
    if (isset($this->node->status)) {
      $output = $this->node->status;
    }
    return $output;
  }

  /**
   * @return integer, date unix stamp for quote order time
   */
  public function createdUnixStamp() {
    $output = NULL;
    if (isset($this->node->created)) {
      $output = $this->node->created;
    }
    return $output;
  }
  /**
   * @return integer, date unix stamp
   */
  public function createdValue($format = NULL) {
    if (!$format) {
      $format = "Y-m-d";
    }

    $output = NULL;
    $stamp = $this->createdUnixStamp();
    if ($stamp) {
      $output = format_date($stamp, 'custom', $format);
    }
    return $output;
  }

  /** - - - - - - node link - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return link, $this->nodeType()
   */
  public function nodeEditLink() {
    $output = base_path() . 'manage/node/edit/' . $this->nid;
    return $output;
  }
  /**
   * @return integer, date unix stamp
   */
  public function nodeViewLink() {
    $output = base_path() . $this->nodeType() . '/node/view/' . $this->nid;
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
}

/** - - - - - - common node - - - - - - - - - - - - - - - - - - - - - - - -  */
/**
 * class
   $JobsInfo = new JobsInfo($nid);
   $JobsInfo->clientName();
 */
class JobsInfo extends NodeInfo {
  /**
   * @return Integer, Term Tid
   */
  public function clientTid() {
    $output = NULL;
    if (isset($this->node->field_quote_client['und'][0]['target_id'])) {
      $output = $this->node->field_quote_client['und'][0]['target_id'];
    }
    return $output;
  }
  /**
    * @return String, Term Property
    */
  public function clientName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->clientTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }
    return $output;
  }
  /**
   * @return Object, Term Property
   */
  public function clientObject() {
    $output = NULL;

    $TermClientInfo = new TermClientInfo($this->clientTid());
    if(!empty($TermClientInfo)) {
      $output = $TermClientInfo;
    }
    return $output;
  }

  /**
   * @return integer, date unix stamp for quote order time
   */
  public function datePostedTimeUnixStamp() {
    $output = NULL;
    if (isset($this->node->field_jobs_date_posted['und'][0]['value'])) {
      $output = $this->node->field_jobs_date_posted['und'][0]['value'];
    }
    return $output;
  }
  /**
   * @return integer, date unix stamp
   */
  public function datePostedTimeValue($format = NULL) {
    if (!$format) {
      $format = "Y-m-d";
    }

    $output = NULL;
    $stamp = $this->datePostedTimeUnixStamp();
    if ($stamp) {
      $output = format_date($stamp, 'custom', $format);
    }
    return $output;
  }


  /** - - - - - - other - - - - - - - - - - - - - - - - - - - - - - - - - -  */
}
