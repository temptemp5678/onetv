<?php

/**
 * callback from hook_menu()
 */
function _jsoninfo_jobboard_jobs_list() {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonJobboardJobsList());
}
/**
 * callback from hook_menu()
 */
function _jsoninfo_jobboard_jobs_map() {
  $JsonData = new JsonData();
  drupal_json_output($JsonData->jsonJobboardJobsMap());
}

/**
 * callback from hook_menu()
 */
function _jsoninfo_jobboard_jobs_geomap() {
  $output = '{
    "type": "Feature",
    "geometry": {
      "type": "Point",
      "coordinates": [42.22, -81.82]
    },
    "properties": {
      "name": "Dinagat Islands"
    }
  }';

  drupal_json_output($output);
}
