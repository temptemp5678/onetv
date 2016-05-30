<?php

/**
 * Implements page_callback(), callback from hook_menu()
 */
function _epg_program_view($nid = NULL) {
  $output = NULL;
  if ($nid) {
    $node = node_load($nid);
    $EpgInfo = new EpgInfo($nid);
    $output .= '<div class="panel panel-default">';
      $output .= '<div class="panel-heading bg-4ab2de color-fff">';
        $output .= $EpgInfo->fieldTargetIdObject('field_epg_channel')->termName();
        $output .= ' ';
        $output .= $EpgInfo->dateTimeValue();
      $output .= '</div>';
      $output .= '<div class="panel-body bg-ffffff padding-0">';
        if (is_array($EpgInfo->fieldValueAllArray('field_epg_program'))) {
          foreach ($EpgInfo->fieldValueAllArray('field_epg_program') as $key => $row) {
            $output .= $row['value'];
          }
        }
      $output .= '</div>';
    $output .=' </div>';

  }

  return $output;
}
