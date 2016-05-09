<?php
/**
 * @file
 */

/**
 * class
 $NodeAction = new NodeAction($para);
 $NodeAction->updateFields($para);
 */
class NodeJsonAction {
  protected $node_type = NULL;

  /**
   * @parameter is nid or node object
   */
  function __construct($param){
    if (is_string($param)) {
      // Returns a list of all the available node types
      if (in_array($param, array_keys(node_type_get_types()))) {
        $this->node_type = $param;
      }
    }
  }

  /** - - - - - - action - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @parameter is nid or node object
   *  node_save()
   */
  public function insertNode() {
    global $user;

    // We create a new node object
    $node = new stdClass();
    $node->type = $this->node_type;
    $node->title = "Default Title";
    $node->language = LANGUAGE_NONE;

    // Set some default values.
    node_object_prepare($node);
    $node->uid = $user->uid;

    // Prepare node for a submit and saving
    $node = node_submit($node);
    node_save($node);

    // node_save() does not return a value. It instead populates the $node object.
    // Thus to check if the save was successful, we check the nid.
    // $node_id = $node->nid;
    // return $node_id;
  }

  /**
   *  node_save() with Fields
   */
  public function insertNodeFields($fields = array(), $title = NULL) {
    global $user;

    $node_title = "Default Article";
    if ($title) {
      $node_title = $title;
    }

    // We create a new node object
    $node = new stdClass();
    $node->type = $this->node_type;
    $node->title = $node_title;
    $node->language = LANGUAGE_NONE;

    // Set some default values.
    node_object_prepare($node);
    $node->uid = $user->uid;

    /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    if (is_array($fields)) {
      // custom fields
      foreach ($fields as $field_name => $row) {
        $field_info = field_info_field($field_name);
        if ($field_info) {
          $field_type = $field_info['type'];

          switch ($field_type) {
            case 'datestamp':
            case 'list_integer':
            case 'number_integer':
            case 'text':
            case 'text_long':
              foreach ($row['und'] as $key => $value) {
                $node->{$field_name}[$node->language][$key]['value'] = $value;
              }
              break;
            case 'entityreference':
              foreach ($row['und'] as $key => $value) {
                $node->{$field_name}[$node->language][$key]['target_id'] = $value;
              }
              break;

            default:
              break;
          }
        }
      }
    }

    /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    // Prepare node for a submit and saving
    $node = node_submit($node);
    node_save($node);

    $nid = $node->nid;
    watchdog('jsonservice', 'node json action insertNode() nid: @nid', array('@nid' => $nid));
  }

  /** Update field  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /**
   * Update field
   */
  public function updateFields($nid = NULL, $fields = array()) {
    $node = node_load($nid);

    if (isset($node)) {
      // custom fields
      foreach ($fields as $field_name => $row) {
        $field_info = field_info_field($field_name);
        if ($field_info) {
          $field_type = $field_info['type'];

          switch ($field_type) {
            case 'datestamp':
            case 'list_integer':
            case 'number_integer':
            case 'text':
            case 'text_long':
              $node->{$field_name}['und'] = array();      // set empty firstly
              if (isset($row['und'])) {
                foreach ($row['und'] as $key => $value) {
                  $node->{$field_name}['und'][$key]['value'] = $value;
                }
              }
              break;
            case 'entityreference':
              $node->{$field_name}['und'] = array();      // set empty firstly
              if (isset($row['und'])) {
                foreach ($row['und'] as $key => $value) {
                  $node->{$field_name}['und'][$key]['target_id'] = $value;
                }
              }
              break;

            default:
              break;
          }
        }
      }

      // It's good to call field_attach_presave()
      field_attach_presave('node', $node);
      field_attach_update('node', $node);
    }
  }

  /** Update One Specify field  - - - - - - - - - - - - - - - - - - - - */
  /**
   * @param, sco Adb Sco ID
   */
  public function updateScoId($meeting_nid = NULL, $sco_id = NULL) {
    $node = node_load($meeting_nid);
    if (isset($node)) {
      $field_language = field_language('node', $node, 'field_meeting_adbscoid');
      $node->field_meeting_adbscoid[$field_language][0]['value'] = $sco_id;

      // It's good to call field_attach_presave()
      field_attach_presave('node', $node);
      field_attach_update('node', $node);
    }
  }

}

/**
 * class
 $NodeJsonAnswersetAction = new NodeJsonAnswersetAction();
 $NodeJsonAnswersetAction->updateFields($para);
 */
class NodeJsonAnswersetAction extends NodeJsonAction {
    /**
   *  node_save() with Fields
   */
  public function insertNodeFields($fields = array(), $title = NULL) {
    global $user;

    $node_title = "Evaluation from JSON";
    if ($title) {
      $node_title = $title;
    }

    // We create a new node object
    $node = new stdClass();
    $node->type = $this->node_type;
    $node->title = $node_title;
    $node->language = LANGUAGE_NONE;

    // Set some default values.
    node_object_prepare($node);
    $node->uid = $user->uid;

    /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    if (is_array($fields)) {
      // custom fields
      foreach ($fields as $field_name => $row) {
        $field_info = field_info_field($field_name);

        if ($field_info) {
          $field_type = $field_info['type'];

          switch ($field_type) {
            case 'answersetfield':                            // custom field
              $node->{$field_name}['und'] = array();          // set empty firstly
              if (isset($row['und'])) {
                foreach ($row['und'] as $key => $value) {
                  $node->{$field_name}['und'][$key]['answerset_queslibr_tid'] = $value['answerset_queslibr_tid'];
                  $node->{$field_name}['und'][$key]['answerset_quesfield_tid'] = $value['answerset_quesfield_tid'];
                  $node->{$field_name}['und'][$key]['answerset_answer'] = $value['answerset_answer'];
                }
              }
              break;

            case 'entityreference':
              foreach ($row['und'] as $key => $value) {
                $node->{$field_name}[$node->language][$key]['target_id'] = $value;
              }
              break;

            default:
              break;
          }
        }
      }
    }

    /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    // Prepare node for a submit and saving
    $node = node_submit($node);
    node_save($node);

    $nid = $node->nid;
    watchdog('jsonservice', 'node json action insertNode() nid: @nid', array('@nid' => $nid));
  }

  /** Update field  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /**
   * Update field
   */
  public function updateFields($nid = NULL, $fields = array()) {
    $node = node_load($nid);

    if (isset($node)) {
      // custom fields
      foreach ($fields as $field_name => $row) {
        $field_info = field_info_field($field_name);
        if ($field_info) {
          $field_type = $field_info['type'];

          switch ($field_type) {
            case 'answersetfield':                            // custom field
              $node->{$field_name}['und'] = array();          // set empty firstly
              if (isset($row['und'])) {
                foreach ($row['und'] as $key => $value) {
                  $node->{$field_name}['und'][$key]['answerset_queslibr_tid'] = $value['answerset_queslibr_tid'];
                  $node->{$field_name}['und'][$key]['answerset_quesfield_tid'] = $value['answerset_quesfield_tid'];
                  $node->{$field_name}['und'][$key]['answerset_answer'] = $value['answerset_answer'];
                }
              }
              break;

            case 'entityreference':
              $node->{$field_name}['und'] = array();          // set empty firstly
              foreach ($row['und'] as $key => $value) {
                $node->{$field_name}[$node->language][$key]['target_id'] = $value;
              }
              break;

            default:
              break;
          }
        }
      }

      // It's good to call field_attach_presave()
      field_attach_presave('node', $node);
      field_attach_update('node', $node);
    }
  }
}

