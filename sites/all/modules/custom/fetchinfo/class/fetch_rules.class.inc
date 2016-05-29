<?php
/**
 * @file
 */

/**
 * class
  $FetchRules = new FetchRules();
  $FetchRules->divArea();

    $FetchRules = new FetchRules();
    //$filter = $FetchRules->filterContent($FetchRules->divArea(), $FetchRules->guangXiContent());
    // $filter = $FetchRules->filterContent($FetchRules->divArea(), file_get_contents('http://program.gxtv.cn'));
    preg_match_all("/<div class=\"Program_guide\">(.*?)</div></div>/", file_get_contents('http://program.gxtv.cn'), $filter);
    dpm($filter);
 */
class FetchRules {
  /**
   * tid = 2,
   * @return, tids array
   */
  public function divArea() {
    $output = "/<div class=\"Program_guide\">(.*?)</div></div>/";
    return $output;
  }

  public function filterContent($channel_rule = NULL, $page_raw_content = NULL) {
    $output = NULL;

    if ($channel_rule) {
      preg_match_all($channel_rule, $page_raw_content, $matches);
      $output = $matches;
    }

    return $output;
  }

  /**
   * @param, Channel Tid
   * @return
   */
  public function guangXiRule() {
    $output = NULL;

    return $output;
  }

  /** - - - - - - content - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * tid = 2,
   * @return, tids array
   */

}
