<?php
/**
 * @file
 */

/**
 * class
 * $TermAction = new TermAction($para);
 */
class TermAction {
  protected $tid;
  protected $term = NULL;

  /**
   * @parameter is tid, or term
   */
  function __construct($param){

    if (is_numeric($param)) {
      $term = taxonomy_term_load($param);
      if ($term) {
        $this->term = $term;
        $this->tid = $param;
      }
    }
    else if (is_object($param)) {
      if (isset($param->tid)) {
        $this->term = $param;
        $this->tid = $param->tid;
      }
    }
  }

  /** - - - - - - action - - - - - - - - - - - - - - - - - - - - - - - - - -  */

}

/**
 * class
   $TermClientAction = new TermClientAction($tid);
   $TermClientAction->updateClientManageUser($uid);
 */
class TermClientAction extends TermAction {
  /**
   * @parameter
   */
  public function addClientManageUser($uid = NULL) {
    if (!$uid) {
      return;
    }

    $UserInfo = new UserInfo($uid);
    $UserInfo->userUid();

    $output = NULL;
    $action = TRUE;

    // use a new variable to taxonomy_term_load()
    $new_term = taxonomy_term_load($this->tid);

    if (isset($new_term->field_client_manage['und'][0]['target_id'])) {
      foreach ($new_term->field_client_manage['und'] as $key => $value) {
        if ($uid == $value['target_id']) {
          $action = FALSE;
        }
      }
    }
    /** - - - - - - action - - - - - - - - - - - - - - - - - - - - - - - - -  */
    /**
     * $term = taxonomy_term_load($this->tid); still load cache $term, can't update
     * so use entity_metadata_wrapper way instead of $term
     */
    if ($action) {
      $new_term->field_client_manage['und'][]['target_id'] = $uid;
      field_attach_presave('term', $new_term);
      field_attach_update('term', $new_term);
    }

    $term_wrapper = entity_metadata_wrapper('taxonomy_term', $new_term);

    $term_wrapper->save();
  }

  /**
   * @parameter
   */
  public function removeClientManageUser($uid = NULL) {
    if (!$uid) {
      return;
    }

    $output = NULL;

    // use a new variable to taxonomy_term_load()
    $new_term = taxonomy_term_load($this->tid);

    if (isset($new_term->field_client_manage['und'][0]['target_id'])) {
      foreach ($new_term->field_client_manage['und'] as $key => $value) {
        if ($uid == $value['target_id']) {
          $action_key = $key;
        }
      }
    }

    /** - - - - - - action - - - - - - - - - - - - - - - - - - - - - - - - -  */
    // $action_key is maybe equle to "0"
    if (isset($action_key)) {
      $term_wrapper = entity_metadata_wrapper('taxonomy_term', $new_term);

      // unset($wrapper->field_foobar[$delta]);
      // $wrapper->save();
      unset($term_wrapper->field_client_manage[$action_key]);

      $term_wrapper->save();
    }
  }

}
