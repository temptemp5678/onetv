<?php
/**
 * @file
 */

/**
 * class
  $FetchAction = new FetchAction();
  $FetchAction->fetchAllChannel();
 */
class FetchAction {
  /** - - - - - - action - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @param, Channel Status is Enable or Disable
   * @return, tids array
   */
  public function allChannelTids($enable = TRUE) {
    $channel_tids = array();

    $terms = taxonomy_get_tree(2);
    if (is_array($terms)) {
      foreach ($terms as $term) {
        $TermChannelInfo = new TermChannelInfo($term->tid);
        if ($enable) {
          if ($TermChannelInfo->fieldValue('field_channel_status') == 1) {
            $channel_tids[] = $term->tid;
          }
        }
        else {
          $channel_tids[] = $term->tid;
        }
      }
    }

    return $channel_tids;
  }

  /**
   * @param, Channel Status is Enable or Disable
   * @return, tids array
   */
  public function checkEpgNid($channel_tid = NULL, $channel_program_date = NULL) {
    // timezone is site timezone
    // $d2 = new DateTime($channel_program_date, new DateTimeZone('Asia/Hong_Kong'));
    $d1 = new DateTime($channel_program_date);
    $channel_program_date_timestamp = $d1->getTimestamp();

    $NodeEpgQuery = new NodeEpgQuery();
    $nids = $NodeEpgQuery->nodesByBundle(array('epg'));
    $nids = $NodeEpgQuery->nodesByChannelTids(array($channel_tid), $nids);
    $nids = $NodeEpgQuery->nodesByDate($channel_program_date_timestamp, $nids);

    $output = NULL;
    if (is_array($nids)) {
      $output = current($nids);
    }
    else {
      $NodeEpgAction = new NodeEpgAction('epg');
      $output = $NodeEpgAction->insertNodeByDateField($channel_program_date_timestamp);
    }

    return $output;
  }

  /**
   * @param, batch to call
   * @return,
   */
  public function fetchAllChannel($enable = TRUE) {
    $channel_tids = $this->allChannelTids($enable);

    if (is_array($channel_tids)) {
      foreach ($channel_tids as $channel_tid) {
        $page_raw_content = $this->getChannelRawContent($channel_tid);
        $channel_program     = $this->getChannelProgram($channel_tid, $page_raw_content);

        if ($channel_program) {
          $node_nid = $this->checkEpgNid($channel_tid, $channel_program['program_date']);

          $NodeAction = new NodeAction('epg');
          $NodeAction->updateFields($node_nid, $channel_program);
        }
      }
    }
  }

  /**
   * filter Program Content
   * @param, Channel Tid
   * @return

     $channel_tid = 2;
     $FetchAction = new FetchAction();
     $contents = $FetchAction->filterContent($channel_tid, $FetchAction->getContentByCurl('http://program.gxtv.cn'));

     dpm($contents[0]);

     $node_nid = $FetchAction->checkEpgNid($channel_tid, '2016-05-28');
dpm($node_nid);


     $channel_program = array();
     $channel_program['field_epg_program']['und'] = $contents[0];
     $NodeEpgAction = new $NodeEpgAction('epg');
     $NodeEpgAction->updateFields($node_nid, $channel_program);
   */
  public function filterContent($channel_tid = NULL, $page_raw_content = NULL) {
    $output = NULL;
    $divRules = NULL;
    $cleanContent = NULL;

    switch ($channel_tid) {
      case 2:
        $FetchRulesChannel2 = new FetchRulesChannel2();
        $cleanContent = $FetchRulesChannel2->cleanContent($page_raw_content);
        $divRules     = $FetchRulesChannel2->divRules();
        break;

      default:
        break;
    }

    if (is_array($divRules)) {
      foreach ($divRules as $channel_rule) {
        preg_match_all($channel_rule, $cleanContent, $matches);
        $cleanContent = $matches[0][0];
      }

      $output = $matches;
    }

    return $output;
  }

  /**
   * use rule to get program date and content
   * @param, Channel Tid
   * @return,
     array(
       'program_date' => 2016-05-24
       'program_content' => array(),
     );
   */
  public function getChannelProgram($channel_tid = NULL, $page_raw_content = NULL) {
    $output = NULL;

    if ($channel_tid) {
      $TermChannelInfo  = new TermChannelInfo($channel_tid);
      $channel_url      = $TermChannelInfo->fieldValue('field_channel_url');

      if ($channel_url && $channel_rule) {
        $output['program_date']    = format_date(time(), 'custom', 'Y-m-d', 'Hongkong');
        $output['program_content'] = filterContent($channel_tid, $page_raw_content);
      }
    }

    return $output;
  }

  /**
   * @param, Channel Tid
   * @return
   */
  public function getChannelRawContent($channel_tid = NULL) {
    $output = NULL;

    if ($channel_tid) {
      $TermChannelInfo = new TermChannelInfo($channel_tid);
      $channel_url     = $TermChannelInfo->fieldValue('field_channel_url');
      if ($channel_url) {
        $output = $this->getContentByCurl($channel_url);
        dpm($output);
      }
    }

    return $output;
  }

  /**
   * instead of using file_get_contents($channel_url);
   */
  function getContentByCurl($Url = NULL) {
    if (!function_exists('curl_init')){
      die('CURL is not installed!');
    }

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $Url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    $result = curl_exec($ch);
    if ($result === false) {
      throw new Exception('Can not download URL');
    }
    else {
      $output = $result;
    }

    curl_close($ch);

    return $output;
  }

}
