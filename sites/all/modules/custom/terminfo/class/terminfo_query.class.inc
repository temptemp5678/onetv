<?php
/**
 * @file
 */

/**
 * class
 * $TermQuery = new TermQuery();
 * dpm($TermQuery->allOrders());
 */
class TermQuery {

  /** - - - - - - field - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @parameter is single number
   *
   * @return Array
   * Program Child Tid
   */
  public function allTerms () {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'taxonomy_term');

    $result = $query->execute();

    $program_tid_array = NULL;
    if (isset($result['taxonomy_term'])) {
      if (count($result['taxonomy_term']) > 0 ) {
        $program_tid_array = array_keys($result['taxonomy_term']);
      }
    }
    return $program_tid_array;
  }

  /**
   * @parameter is single number
   *
   * @return Array
   * Program Child Tid
   */
  public function allClientTerms () {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'taxonomy_term');
    $query->entityCondition('bundle', array('client'));

    $result = $query->execute();
    $program_tid_array = NULL;
    if (isset($result['taxonomy_term'])) {
      if (count($result['taxonomy_term']) > 0 ) {
        $program_tid_array = array_keys($result['taxonomy_term']);
      }
    }
    return $program_tid_array;
  }
}
