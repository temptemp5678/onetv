<?php
/**
 * @file
 */

/**
 * class
 $TermJsonAction = new TermJsonAction();
 $TermJsonAction->updateFields($para);
 */
class TermJsonAction {

  /** - - - - - - action - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   *  save
   */
  public function insertTerm($vid = NULL, $fields = array()) {
    if (!empty($fields['title'])) {
      // Create a new term object
      $term = new stdClass();
      $term->name = $fields['title'];
      $term->vid = $vid;
      $term->parent = 0;
      $term->description = '';

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
                $term->{$field_name}['und'][$key]['value'] = $value;
              }
              break;
            case 'entityreference':
              foreach ($row['und'] as $key => $value) {
                $term->{$field_name}['und'][$key]['target_id'] = $value;
              }
              break;

            default:
              break;
          }
        }
      }
    }

    // Prepare node for a submit and saving
    taxonomy_term_save($term);

    $tid = $term->tid;
    watchdog('jsonservice', 'term json action insertTerm() tid: @tid', array('@tid' => $tid));
  }

  /** Update field  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /**
   * Update field
   */
  public function updateFields($tid = NULL, $fields = array()) {
    $term = taxonomy_term_load($tid);

    if (isset($term)) {
      if (!empty($fields['title'])) {
        $term->name = $fields['title'];
      }

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
              $term->{$field_name}['und'] = array();        // set empty firstly
              if (isset($row['und'])) {
                foreach ($row['und'] as $key => $value) {
                  $term->{$field_name}['und'][$key]['value'] = $value;
                }
              }
              break;
            case 'entityreference':
              $term->{$field_name}['und'] = array();        // set empty firstly
              if (isset($row['und'])) {
                foreach ($row['und'] as $key => $value) {
                  $term->{$field_name}['und'][$key]['target_id'] = $value;
                }
              }
              break;

            default:
              break;
          }
        }
      }

      // It's good to call field_attach_presave()
      taxonomy_term_save($term);
    }
  }

  /** Delete Term  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /**
   * Delete Term
   */
  public function deleteTerm($tid = NULL) {
    taxonomy_term_delete($tid);
  }

}

/**
 * class
 $TermJsonQuessetFieldAction = new TermJsonQuessetFieldAction();
 $TermJsonQuessetFieldAction->updateFields($para);
 */
class TermJsonQuessetFieldAction extends TermJsonAction {

  /** - - - - - - action - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   *  save
   */
  public function insertTerm($vid = NULL, $fields = array()) {
    if (!empty($fields['title'])) {
      // Create a new term object
      $term = new stdClass();
      $term->name = $fields['title'];
      $term->vid = $vid;
      $term->parent = 0;
      $term->description = '';

      // custom fields
      foreach ($fields as $field_name => $row) {
        $field_info = field_info_field($field_name);
        if ($field_info) {
          $field_type = $field_info['type'];

          switch ($field_type) {
            case 'quessetfield':                            // custom field
              $term->{$field_name}['und'] = array();        // set empty firstly
              if (isset($row['und'])) {
                foreach ($row['und'] as $key => $value) {
                  $term->{$field_name}['und'][$key]['quesset_number'] = $value['quesset_number'];
                  $term->{$field_name}['und'][$key]['quesset_question_tid'] = $value['quesset_question_tid'];
                }
              }
              break;

            default:
              break;
          }
        }
      }
    }

    // Prepare node for a submit and saving
    taxonomy_term_save($term);

    $tid = $term->tid;
    watchdog('jsonservice', 'term json action insertTerm() tid: @tid', array('@tid' => $tid));
  }

  /** Update field  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /**
   * Update field
   */
  public function updateFields($tid = NULL, $fields = array()) {
    $term = taxonomy_term_load($tid);

    if (isset($term)) {
      if (!empty($fields['title'])) {
        $term->name = $fields['title'];
      }

      // custom fields
      foreach ($fields as $field_name => $row) {
        $field_info = field_info_field($field_name);
        if ($field_info) {
          $field_type = $field_info['type'];

          switch ($field_type) {
            case 'quessetfield':                            // custom field
              $term->{$field_name}['und'] = array();        // set empty firstly
              if (isset($row['und'])) {
                foreach ($row['und'] as $key => $value) {
                  $term->{$field_name}['und'][$key]['quesset_number'] = $value['quesset_number'];
                  $term->{$field_name}['und'][$key]['quesset_question_tid'] = $value['quesset_question_tid'];
                }
              }
              break;

            default:
              break;
          }
        }
      }

      // It's good to call field_attach_presave()
      taxonomy_term_save($term);
    }
  }
}
