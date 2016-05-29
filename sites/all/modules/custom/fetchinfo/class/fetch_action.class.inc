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
    $NodeEpgQuery = new NodeEpgQuery();
    $nids = $NodeEpgQuery->nodesByBundle(array('epg'));
    $nids = $NodeEpgQuery->nodesByChannelTids(array($channel_tid), $nids);
    $nids = $NodeEpgQuery->nodesByDate($channel_program_date, $nids);

    $output = NULL;
    if (is_array($nids)) {
      $output = current($nids);
    }
    else {
      $NodeAction = new NodeAction('epg');
      $output = $NodeAction->insertNodeByDateField($channel_program_date);
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
          $node_nid = checkEpgNid($channel_tid, $channel_program['program_date']);

          $NodeAction = new NodeAction('epg');
          $NodeAction->insertNodeFields($channel_program);
          $NodeAction->updateFields($channel_program);
        }
      }
    }
  }

  /**
   * @param, Channel Rule
   * @return
   */
  public function filterContent($channel_rule = NULL, $page_raw_content = NULL) {
    $output = NULL;

    if ($channel_rule) {
      preg_match_all($channel_rule, $page_raw_content, $matches);
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
      $channel_rule     = $this->guangXiRule();

      if ($channel_url && $channel_rule) {
        $output['program_date']    = format_date(time(), 'custom', 'Y-m-d', 'Hongkong');
        $output['program_content'] = filterContent($channel_rule, $page_raw_content);
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
