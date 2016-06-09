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
  public function convertPageCode($contents = NULL) {
    $output = mb_convert_encoding($str, "UTF-8", "GBK");   // 已知原编码为GBK，转换为utf-8
    $output = mb_convert_encoding($str, "UTF-8", "auto");  // 未知原编码，通过auto自动检测后，转换编码为utf-8
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

    return $contents;
  }

  /**
   * @return,
   * $output = '/<div class=\"Program_guide\">(.*?)<\/div>/';
   */
  public function divArea() {

    $output = NULL;
    return $output;
  }

  /**
   * @return,
   * $output = '/<li><span>(.*?)<\/span>(.*?)<\/li>/';
   */
  public function divProgram() {
    $output = NULL;
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
   * @return, remove unwanted characters as "<a href>.. </a>"

     $row = '<li><span class="am">00:28</span> <a title="新安夜空"  href="/tvcolumn/Vig4" tp="12" res="2016-05-30 00:28_Vig4" >新安夜空    </li>';
     $FetchRulesChannel4 = new FetchRulesChannel4();
     dpm($FetchRulesChannel4->removeATag($row));
   */
  public function removeATag($contents = NULL) {
    $contents = preg_replace('/<a (.*?)>/', '', $contents);
    $output = preg_replace('/<\/a>/', '', $contents);

    return $output;
  }

  /**
   * @return, remove unwanted characters as "<a href>.. </a>"

     $row = '<li><span class="am">00:28</span> <a title="新安夜空"  href="/tvcolumn/Vig4" tp="12" res="2016-05-30 00:28_Vig4" >新安夜空    </li>';
     $FetchRulesChannel4 = new FetchRulesChannel4();
     dpm($FetchRulesChannel4->removeATag($row));
   */
  public function removeDivTag($contents = NULL) {
    $output = preg_replace('/<div (.*?)<\/div>/', '', $contents);
    return $output;
  }

  /**
   * @return,
   */
  public function other($contents = NULL) {
    // preg split ($pattern,$subject)用于匹配到的字符进行切断，匹配到一个就断开一次，产生多个数组，，，和php中的explode很像
  }
}

/**
 * class
   Tid is 2, GuagnXi
   $FetchAction = new FetchAction();
   $FetchRulesChannel2 = new FetchRulesChannel2();
   dpm($FetchRulesChannel2->filterContent($FetchAction->getContentByCurl('http://program.gxtv.cn')));
 */
class FetchRulesChannel2 extends FetchRules {
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
   * @return Array, filter result
   */
  public function filterContent($raw_page = NULL) {
    $contents = $this->cleanContent($raw_page);

    preg_match_all($this->divArea(), $contents, $matches);
    $cleanContent = $matches[0][0];

    preg_match_all($this->divProgram(), $cleanContent, $matches);
    $cleanContent = $matches[0];

    $output = $cleanContent;
    return $output;
  }

}

/**
 * class
   Tid is 4, AnHui
   $FetchAction = new FetchAction();
   $FetchRulesChannel4 = new FetchRulesChannel4();
   dpm($FetchRulesChannel4->filterContent($FetchAction->getContentByCurl('http://www.tvmao.com/program_satellite/AHTV1-w1.html')));

   $channel_tid = 4;
    $node_nid = $FetchAction->checkEpgNid($channel_tid, '2016-05-28');
    dpm($node_nid);

    $channel_program = array();
    $channel_program['field_epg_program']['und'] = FetchRulesChannel4->filterContent();
    $NodeEpgAction = new NodeEpgAction('epg');
    $NodeEpgAction->updateFields($node_nid, $channel_program);
 */
class FetchRulesChannel4 extends FetchRules {
  /**
   * @return,
   */
  public function divArea() {
    $output = '/<ul  id="pgrow">(.*?)<\/ul>/s';
    return $output;
  }

  /**
   * @return,
   */
  public function divProgram() {
    $output = '/<li><span class="am">(.*?)<\/span>(.*?)<\/li>/';
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
   * @return Array, filter result
   */
  public function filterContent($raw_page = NULL) {
    $contents = $this->cleanContent($raw_page);

    preg_match_all($this->divArea(), $contents, $matches);
    $cleanContent = $matches[0][0];

    preg_match_all($this->divProgram(), $cleanContent, $matches);
    $cleanContent = $matches[0];

    $output = NULL;
    if (isset($cleanContent)) {
      foreach ($cleanContent as $key => $value) {
        $output[] = $this->removeDivTag($this->removeATag($value));
      }
    }

    return $output;
  }

}

/**
 * class
   Tid is 6, 全纪实 SiTV
 */
class FetchRulesChannel6 extends FetchRules {
  /**
   * @return,
   */
  public function divArea() {
    $output = '/<ul  id="pgrow">(.*?)<\/ul>/s';
    return $output;
  }

  /**
   * @return,
   */
  public function divProgram() {
    $output = '/<li><span class="am">(.*?)<\/span>(.*?)<\/li>/';
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
   * @return Array, filter result
   */
  public function filterContent($raw_page = NULL) {
    $contents = $this->cleanContent($raw_page);

    preg_match_all($this->divArea(), $contents, $matches);
    $cleanContent = $matches[0][0];

    preg_match_all($this->divProgram(), $cleanContent, $matches);
    $cleanContent = $matches[0];

    $output = NULL;
    if (isset($cleanContent)) {
      foreach ($cleanContent as $key => $value) {
        $output[] = $this->removeDivTag($this->removeATag($value));
      }
    }

    return $output;
  }

}
