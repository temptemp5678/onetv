<?php

/**
 * class
   $JsonDataUnit = new JsonDataUnit();
   $JsonDataUnit->termCityJsonFile();
   $JsonDataUnit->userSpeakerDetails();
 *
 */
class JsonDataUnit{

  /** - - - - - Node Json- - - - - - - - - - - - - - - */


  /** - - - - - page - - - - - - - - - - - - - - - - - - - - - - */
  /**
   * @return
   */
  public function jobboardJobsList($nids = array()) {
    $nodes = node_load_multiple($nids);

    $output = array();
    foreach ($nodes as $key => $node) {
      $JobsInfo = new JobsInfo($node->nid);

      if ($JobsInfo->fieldValue('field_jobs_latitude') && $JobsInfo->fieldValue('field_jobs_longitude')) {
        $output[] = array(
          "description"  => $JobsInfo->fieldSafeValue('field_jobs_description'),
          "careerLevel"  => $JobsInfo->fieldTargetIdObject('field_jobs_career_level')->termName(),
          "datePostedTimeValue" => $JobsInfo->datePostedTimeValue(),
          "nodeNid"  => $JobsInfo->nodeNid(),
          "nodeTitle"  => $JobsInfo->nodeTitle(),
          "nodeViewLink"  => $JobsInfo->nodeViewLink(),
          "jobType"  => $JobsInfo->fieldTargetIdObject('field_jobs_job_type')->termName(),
          "town"  => $JobsInfo->fieldTargetIdObject('field_jobs_town')->termName(),
          "industry"  => $JobsInfo->fieldTargetIdObject('field_jobs_industry')->termName(),
        );
      }
    }
    return $output;
  }
  /**
   * @return
   */
  public function jobboardJobsMap($nids = array()) {
    $nodes = node_load_multiple($nids);

    $output = array();
    foreach ($nodes as $key => $node) {
      $JobsInfo = new JobsInfo($node->nid);

      if ($JobsInfo->fieldValue('field_jobs_latitude') && $JobsInfo->fieldValue('field_jobs_longitude')) {
        $output[] = array(
          "coordinates" => array($JobsInfo->fieldValue('field_jobs_latitude'), $JobsInfo->fieldValue('field_jobs_longitude')),
          "popupText"  => $JobsInfo->nodeTitle(),
        );
      }
    }
    return $output;
  }

  /** - - - - - Term Standard Json- - - - - - - - - - - - - - - - - - - - - - */
  /**
   * @return Term Array data by specify VID
   */
  public function termStandardJson($vid = NULL, $class_name = NULL, $basic = NULL) {
    if ($class_name) {
      $all_term_array = taxonomy_get_tree($vid);

      if (is_array($all_term_array)) {
        foreach ($all_term_array as $term_key => $term_row) {
          // $TermProgramInfo = new TermProgramInfo($term_row->tid);
          $TermClassInfo = new $class_name($term_row->tid);

          if ($basic) {
            $output[] = $TermClassInfo->basicMethodsValue();
          }
          else {
            $output[] = $TermClassInfo->allMethodsValue();
          }
        }
      }
    }

    return $output;
  }


  /** - - - - - Query Table Json- - - - - - - - - - - - - - - - - - - - -   */


  /** - - - - - User - - - - - - -- - - - - - - - - - - - - - - - - - - -   */

}

/**
 * class
   $JsonData = new JsonData();
   $JsonData->sourceArrayData();
 *
 */
class JsonData extends JsonDataUnit {

  /** - - - - - - page - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return Term Array data
   */
  public function jsonJobboardJobsList() {
    $NodeQuery = new NodeQuery();
    $nids = $NodeQuery->nodesByBundle('jobs');

    $output = $this->jobboardJobsList($nids);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function jsonJobboardJobsMap() {
    $NodeQuery = new NodeQuery();
    $nids = $NodeQuery->nodesByBundle('jobs');

    $output = $this->jobboardJobsMap($nids);
    return $output;
  }

  /** - - - - - - Program - - - - - - - - - - - - - - - - - - - - - - - -  */

  /** - - - - - - user - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return Array data
   */
  public function jsonUserList() {
    $output = NULL;

    $output['userList'] = $this->allUserList();
    $output['termBusinessUnit'] = $this->termBusinessUnit();
    $output['termCity'] = $this->termCityArrayFile();
    $output['termProvince'] = $this->termProvince();
    $output['termTherapeuticArea'] = $this->termTherapeuticArea();

    return $output;
  }
  /**
   * @return Array data
   */
  public function jsonUserProfile($uid = NULL) {
    $output = $this->userProfileFields($uid);
    return $output;
  }
  /**
   * @return Array data
   */
  public function jsonUserSpeakerDetails($uid = NULL) {
    $output = $this->userSpeakerDetails($uid);
    return $output;
  }

}
