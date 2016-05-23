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
  public function insertNode($fields = array()) {
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
}

/**
 * class
   $NodeQuoteAction = new NodeQuoteAction('meeting');
   $NodeQuoteAction->updateToConfirm($nid);
 */
class NodeQuoteAction extends NodeAction {
  /**
   * @parameter
   */
  public function addInviteRepId($meeting_nid = NULL, $rep_uid= NULL) {
    $node = node_load($meeting_nid);
    $UserInfo = new UserInfo($rep_uid);

    $output = NULL;
    $action = FALSE;
    if (isset($node)) {
      if (in_array(7, $UserInfo->userRolesRid())) {
        $MeetingInfo = new MeetingInfo($meeting_nid);

        if (is_array($MeetingInfo->invitedrep())) {
          if (in_array($rep_uid, $MeetingInfo->invitedrep())) {
            // user already in list
          }
          else {
            $action = TRUE;
          }
        }
        else {
          $action = TRUE;
        }
      }
      else {
        $output = t('User is not Rep role');
      }

    }

    if ($action) {
      $field_language = field_language('node', $node, 'field_meeting_invitedrep');
      $node->field_meeting_invitedrep['und'][]['target_id'] = $rep_uid;

      field_attach_presave('node', $node);
      field_attach_update('node', $node);
    }
  }

  /**
   * @parameter is nid or node object
   *  node_save()
   */
  public function insertNode($fields = array()) {
    global $user;

    // We create a new node object
    $node = new stdClass();
    $node->type = $this->node_type;
    $node->title = "Default Meeting";
    $node->language = LANGUAGE_NONE;

    // Set some default values.
    node_object_prepare($node);
    $node->uid = $user->uid;


    /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    if (!is_array($fields)) {
      return;
    }

    // custom fields
    foreach ($fields as $field_name => $value) {
      $field_info = field_info_field($field_name);
      if ($field_info) {
        $field_type = $field_info['type'];

        switch ($field_type) {
          case 'datestamp':
          case 'list_integer':
          case 'number_integer':
          case 'text':
          case 'text_long':
            $node->{$field_name}[$node->language][0]['value'] = $value;
            break;
          case 'entityreference':
            if ($value) {
              $node->{$field_name}[$node->language][0]['target_id'] = $value;
            }
            break;

          default:
            break;
        }
      }
    }

    /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    // Prepare node for a submit and saving
    $node = node_submit($node);
    node_save($node);

    $nid = $node->nid;
    watchdog('nodeinfo', 'node action insertNode() nid: @nid', array('@nid' => $nid));

    // node_save() does not return a value. It instead populates the $node object.
    // Thus to check if the save was successful, we check the nid.
    // $node_id = $node->nid;
    // return $node_id;
  }

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
