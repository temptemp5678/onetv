<?php
/**
 * @file
 */

/**
 * class
 * $NodeAction = new NodeAction($para);
 */
class NodeAction {
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
    $node->title = 'Standard ' . $this->node_type . ' Node';
    $node->language = LANGUAGE_NONE;

    // Set some default values.
    node_object_prepare($node);
    $node->uid = $user->uid;

    // Prepare node for a submit and saving
    $node = node_submit($node);
    node_save($node);

    // node_save() does not return a value. It instead populates the $node object.
    // Thus to check if the save was successful, we check the nid.
    $node_nid = $node->nid;
    return $node_nid;
  }

  /**
   *  node_save() with Fields
   */
  public function insertNodeByFields($fields_content = array(), $title = NULL) {
    global $user;

    $node_title = 'Standard ' . $this->node_type . ' Node';
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
    if (is_array($fields_content)) {
      // custom fields
      foreach ($fields_content as $field_name => $row) {
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

    $node_nid = $node->nid;
    watchdog('nodeinfo', 'node action insertNode() nid: @nid', array('@nid' => $node_nid));

    return $node_nid;
  }

}

/**
 * class
   $NodeQuoteAction = new NodeQuoteAction('meeting');
   $NodeQuoteAction->updateToConfirm($nid);
 */
class NodeEpgAction extends NodeAction {
  /**
   *  node_save() with Fields
   */
  public function insertNodeByDateField($date = NULL, $title = NULL) {
    global $user;

    $node_title = 'Standard ' . $this->node_type . ' Node';
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

    // custom fields
    if ($date) {
      $field_name = 'field_epg_date';
      $node->{$field_name}[$node->language][$key]['value'] = $date;
    }

    // Prepare node for a submit and saving
    $node = node_submit($node);
    node_save($node);

    $node_nid = $node->nid;
    watchdog('nodeinfo', 'node action insertNode() nid: @nid', array('@nid' => $node_nid));

    return $node_nid;
  }

  /** Update field  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /**
   * Update field
   */
  public function updateFields($nid = NULL, $fields_content = array()) {
    $node = node_load($nid);
    if ($node) {
      // custom fields
      foreach ($fields_content as $field_name => $row) {
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
