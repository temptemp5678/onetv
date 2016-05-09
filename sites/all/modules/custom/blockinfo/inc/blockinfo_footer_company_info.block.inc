<?php
/**
 * @file
 *
 */

/**
 * callback from hook_block_view()
 */
function _blockinfo_footer_company_info() {
  $output = '';
  $output .= '<div class="othercontent-footer-company-info-wrapper hidden-print">';

    $output .= '<div class="text-center">';
      $output .= '<div>' . t('北京万博信普通讯技术有限公司') . ' ' . t('电话') . ': +86 10 6530 2100 </div>';
      $output .= '<div class="color-ddd">' . t('北京市朝阳区南磨房路29号1号楼旭捷大厦10层') . '</div>';
      $output .= '<div class="color-ddd">';
      $output .= '</div>';
    $output .= '</div>';

    $output .= '<div class="text-center">';
      $output .= '<div>One Band &#8226; One Dream</div>';
    $output .= '</div>';

    $output .= '<div class="text-center">';
      $output .= '<div> V2.' . (date("y") +  date("m")) . '.' . date("d") .'</div>';
    $output .= '</div>';

  $output .= '</div>';

  return $output;
}
