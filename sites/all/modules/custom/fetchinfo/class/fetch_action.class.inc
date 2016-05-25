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

dpm($TermChannelInfo->fieldValue('field_channel_status'));
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
    $NodeEpgQuery->nodesByChannelTids(array($channel_tid), $nids);

    $NodeAction = new NodeAction('epg');
    $NodeAction->insertNodeFields($channel_program_date);

  }

  /**
   * @param, Channel Status is Enable or Disable
   * @return, tids array
   */
  public function fetchAllChannel($enable = TRUE) {
    $channel_tids = $this->allChannelTids($enable);
    dpm($channel_tids);
    if (is_array($channel_tids)) {
      foreach ($channel_tids as $channel_tid) {
        dpm($channel_tid);
        $channel_raw_content = $this->getChannelRawContent($channel_tid);
        $channel_program     = $this->getChannelProgram($channel_tid, $channel_raw_content);
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
  public function filterContent($channel_rule = NULL, $channel_raw_content = NULL) {
    $output = NULL;

    if ($channel_rule) {
      preg_match_all($channel_rule, $channel_raw_content, $matches);
      $output = $matches;
    }

    return $output;
  }

  /**
   * @param, Channel Tid
   * @return
   */
  public function getChannelProgram($channel_tid = NULL, $channel_raw_content = NULL) {
    $output = NULL;

    if ($channel_tid) {
      $TermChannelInfo  = new TermChannelInfo($channel_tid);
      $channel_url      = $TermChannelInfo->fieldValue('field_channel_url');
      $channel_rule     = $this->guangXiRule();

      if ($channel_url && $channel_rule) {
        $output['program_date']    = filterContent($channel_rule, $channel_raw_content);
        $output['program_content'] = filterContent($channel_rule, $channel_raw_content);
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
        $output = file_get_contents($channel_url);
      }
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

}
