<?php
/**
 * @file
 */

/**
 * class
   $NodeQuery = new NodeQuery();
   $NodeQuery->nodesByBundle(array('page'));
 */
class NodeQuery {
  /**
   * @parameter, $node_type is array()
   *
   * @return array,
   * all Product NID
   * only NODE_PUBLISHED
   */
  public function nodesByBundle($node_type = array()) {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', $node_type)
      ->propertyCondition('status', NODE_PUBLISHED);

    $result = $query->execute();

    $nid_array = NULL;
    if (isset($result['node'])) {
      if (count($result['node']) > 0 ) {
        $nid_array = array_keys($result['node']);
      }
    }

    return $nid_array;
  }

  /**
   * @parameter, $node_type is array()
   *
   * @return array,
   *  Node both for PUBLISHED or not
   */
  public function allNodesByBundle($node_type = array()) {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', $node_type);

    $result = $query->execute();

    $nid_array = NULL;
    if (isset($result['node'])) {
      if (count($result['node']) > 0 ) {
        $nid_array = array_keys($result['node']);
      }
    }

    return $nid_array;
  }
}

/**
 * class
   $NodeEpgQuery = new NodeEpgQuery();
   $NodeEpgQuery->nodesByChannelTids();
 */
class NodeEpgQuery extends NodeQuery {
  /**
   * @parameter
   *  array,
   *
   * @return array,
   *  nids
   */
  public function nodesByChannelTids($channel_tids = array(), $nids = array()) {
    $output = NULL;

    if (is_array($channel_tids)) {
      $nodes = node_load_multiple($nids);
      if ($nodes) {
        foreach($nodes as $node) {
          $EpgInfo = new EpgInfo($node);
          if (in_array($EpgInfo->fieldTargetId('field_epg_channel'), $channel_tids)) {
            $output[] = $node->nid;
          }
        }
      }
    }

    return $output;
  }

  /**
   * @parameter
   *  array,
   *
   * @return array,
   *  nids
   */
  public function nodesByDate($date = NULL, $nids = array()) {
    $output = NULL;

    if (is_array($channel_tids)) {
      $nodes = node_load_multiple($nids);
      if ($nodes) {
        foreach($nodes as $node) {
          $EpgInfo = new EpgInfo($node);
          if ($EpgInfo->fieldTargetId('field_epg_date') == $date)) {
            $output[] = $node->nid;
          }
        }
      }
    }

    return $output;
  }
}
