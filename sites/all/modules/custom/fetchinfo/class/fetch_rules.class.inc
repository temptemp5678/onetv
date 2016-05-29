<?php
/**
 * @file
 */

/**
 * class
  $FetchRules = new FetchRules();
  $FetchRules->divArea();

  $FetchAction = new FetchAction();
  $FetchRules = new FetchRules();
  $contents = $FetchRules->cleanContent($FetchAction->getContentByCurl('http://program.gxtv.cn'));
  $filter = $FetchRules->filterContent($FetchRules->divArea(), $contents);
  dpm($filter);

  $programs = $FetchRules->filterContent($FetchRules->divProgram(), $filter[0][0]);
  dpm($programs[0]);
 */
class FetchRules {
  /**
   * @return,
   */
  public function divArea() {
    $output = '/<div class=\"Program_guide\">(.*?)<\/div>/';
    return $output;
  }
  /**
   * @return,
   */
  public function divProgram() {
    $output = '/<li><span>(.*?)<\/span>(.*?)<\/li>/';
    return $output;
  }

  /**
   * tid = 2,
   * @return, tids array
   */
  public function cleanContent($contents) {
    $contents = str_replace("\r\n", '', $contents); //清除换行符
    $contents = str_replace("\n", '', $contents);   //清除换行符
    $contents = str_replace("\t", '', $contents);   //清除制表符
    // $contents = str_replace(" ", '', $contents);    //清除空格符
    return $contents ;
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
