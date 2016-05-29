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
   * @return Array
   */
  public function divRules() {
    $output = NULL;

    return $output;
  }

  /**
   * @return, pass contents
   */
  public function cleanContent($contents) {
    return $contents ;
  }

}

/**
 * class
   Tid is 2, GuagnXi
   $FetchRulesChannel2 = new FetchRulesChannel2('meeting');
   $FetchRulesChannel2->divArea($nid);

   $FetchAction = new FetchAction();
   $FetchRulesChannel2 = new FetchRulesChannel2();
   $contents = FetchRulesChannel2->cleanContent($FetchAction->getContentByCurl('http://program.gxtv.cn'));

   $filter = $FetchAction->filterContent(FetchRulesChannel2->divArea(), $contents);
   dpm($filter);

   $programs = $FetchAction->filterContent(FetchRulesChannel2->divProgram(), $filter[0][0]);
   dpm($programs[0]);
 */
class FetchRulesChannel2 extends FetchRules {
  /**
   * @return,
   */
  public function convertPageCode($contents = NULL) {
    $output = mb_convert_encoding($str, "UTF-8", "GBK");   // 已知原编码为GBK，转换为utf-8
    $output = mb_convert_encoding($str, "UTF-8", "auto");  // 未知原编码，通过auto自动检测后，转换编码为utf-8
    return $output;
  }

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
   * @return Array
   */
  public function divRules() {
    $output = array(
      $this->divArea(),
      $this->divProgram(),
    );
    return $output;
  }

  /**
   * @return, tids array
   */
  public function cleanContent($contents = NULL) {
    $contents = str_replace("\r\n", '', $contents); //清除换行符
    $contents = str_replace("\n", '', $contents);   //清除换行符
    $contents = str_replace("\t", '', $contents);   //清除制表符
    // $contents = str_replace(" ", '', $contents);    //清除空格符

    return $contents ;
  }

}
