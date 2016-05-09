<?php

/**
 *

 // Lilly Alliance
 Diabetes in Distinct Populations   -- 2560
 Let's Have a Heart to Heart: Cardiovascular Considerations in Type 2 Diabetes -- 2717
 New vs Old: Antihyperglycemic Treatment Considerations for T2DM -- 2681
 Shine a Light on Type 2 Diabetes -- 2566
 Spotlight on SGLT2 inhibitors -- 2679

 */
// export_data_from_lillyform();
function export_data_from_lillyform() {
  $DashQuery = new DashQuery();
  // allMeetingNid by program tids
  $nids = $DashQuery->allMeetingNid(array(
    // 2635,
    // 2714,
    // 2698,
    // 2712,
    // 2601,
    // 2719,
    // 2605,
    // 2713,
    // // 2663,
    // 2720,
    // // 2708,
    // 2681,
    // 2571,
    // 2721,
    // 2679,
    // 2715,
    // 2707,

    2663,
    2708,
  ));

  foreach($nids as $key => $nid){
    $MeetingInfo = new MeetingInfo($nid);

    $row = '';
    if ($MeetingInfo) {
      if ($MeetingInfo->nid > 0) {
        $row = array(
          '"' . $MeetingInfo->programName() . '"',        // tid
          '"' . $MeetingInfo->multiTherapeuticEvent() . '"',
          '"' . $MeetingInfo->meetingTypeName() . '"',   // tid
          '"' . $MeetingInfo->userGroupName() . '"',     // tid
          '"' . $MeetingInfo->repName() . '"',          // uid
          '"' . $MeetingInfo->speakerName() . '"',      // uid
          '"' . $MeetingInfo->dateTimeStamp() . '"',
          '"' . $MeetingInfo->meetingLocation() . '"',
          '"' . $MeetingInfo->venueName() . '"',
          '"' . $MeetingInfo->meetingAddress() . '"',
          '"' . $MeetingInfo->provinceName() . '"',     // tid
          '"' . $MeetingInfo->cityName() . '"',         // tid
          '"' . $MeetingInfo->meetingPostalCode() . '"',
          '"' . $MeetingInfo->honorarium() . '"',
          '"' . $MeetingInfo->foodCost() . '"',
          '"' . $MeetingInfo->catering() . '"',
          '"' . $MeetingInfo->signaturesNum() . '"',
          '"' . $MeetingInfo->received() . '"',
          '"' . $MeetingInfo->meetingLat() . '"',
          '"' . $MeetingInfo->meetingLon() . '"',
          '"' . $MeetingInfo->nid . '"',
        );

        dpm('array(' . implode(',', $row) . '),');
      }
    }
  }
}

/**
 *
  require_once(DRUPAL_ROOT . '/sites/all/modules/custom/phpdebug/import_export_node.php');
  export_data_from_lillyglobal();
 */
function export_data_from_lillyglobal() {
  $NodeQuery = new NodeQuery();
  $meeting_nids = $NodeQuery->meetingNidsByPrograms(
    array(
      // 2357,
      // 2358,
      // 2356,
      // 2359,
      // 2360,
      // 2361,
      // 2362,
      // 2363,
      // 2364,
      // 2118,
      // 2365,
      // 2293,
      // 2124,
      // 2366,
      // 2367,
      2412,
      2413,
    ),
    $NodeQuery->meetingNids());

  $meeting_nodes = node_load_multiple($meeting_nids);

  foreach($meeting_nodes as $key => $node){
    $MeetingInfo = new MeetingInfo($node->nid);

    $row = '';
    if ($MeetingInfo) {
      if ($MeetingInfo->nodeNid() > 0) {
        $row = array(
          '"' . $MeetingInfo->programName() . '"',        // tid
          '"' . $MeetingInfo->multiTherapeName() . '"',
          '"' . $MeetingInfo->meetingFormatName() . '"',   // tid
          '"' . $MeetingInfo->userGroupName() . '"',     // tid
          '"' . $MeetingInfo->repName() . '"',          // uid
          '"' . $MeetingInfo->speakerName() . '"',      // uid
          '"' . $MeetingInfo->dateUnixStamp() . '"',
          '"' . $MeetingInfo->locationName() . '"',
          '"' . $MeetingInfo->venueName() . '"',
          '"' . $MeetingInfo->address() . '"',
          '"' . $MeetingInfo->provinceName() . '"',     // tid
          '"' . $MeetingInfo->cityName() . '"',         // tid
          '"' . $MeetingInfo->postalCode() . '"',
          '"' . $MeetingInfo->honorarium() . '"',
          '"' . $MeetingInfo->foodCost() . '"',
          '"' . $MeetingInfo->catering() . '"',
          '"' . $MeetingInfo->signatures() . '"',
          '"' . $MeetingInfo->meetingReceivedName() . '"',
          '"' . $MeetingInfo->latitude() . '"',
          '"' . $MeetingInfo->longitude() . '"',
          '"' . $MeetingInfo->nodeNid() . '"',
        );

        dpm('array(' . implode(',', $row) . '),');
      }
    }
  }
}

function _compare_program_name() {
  $program_name = 'New Horizons in Advanced Gastro-esophageal Junction and Gastric Cancer Treatment';

  return $program_name;
}

/**
 * compare
   require_once(DRUPAL_ROOT . '/sites/all/modules/custom/phpdebug/import_export_node.php');
   require_once(DRUPAL_ROOT . '/sites/all/modules/custom/phpdebug/meeting_file.php');
   _compare_lillyform_lillyglobal();
 */
function _compare_lillyform_lillyglobal() {
  $program_name = _compare_program_name();

  // $data_lillyform = meeting_file_data_lillyform();
  // $data_lillyglobal = meeting_file_data_lillyglobal();

  $data_lillyform = meeting_file_data_lillyform_by_program($program_name);
  $data_lillyglobal = meeting_file_data_lillyglobal_by_program($program_name);

  $result = drupal_array_diff_assoc_recursive($data_lillyform, $data_lillyglobal);
  dpm($result);
  print_r($result);
}

/**
 * after compare
   generate meeting key pair
   require_once(DRUPAL_ROOT . '/sites/all/modules/custom/phpdebug/import_export_node.php');
   require_once(DRUPAL_ROOT . '/sites/all/modules/custom/phpdebug/meeting_file.php');
   _generate_meeting_key_pair();
 */
function _generate_meeting_key_pair() {
  $program_name = _compare_program_name();

  // $data_lillyform = meeting_file_data_lillyform();
  // $data_lillyglobal = meeting_file_data_lillyglobal();

  $data_lillyform = meeting_file_data_lillyform_by_program($program_name);
  $data_lillyglobal = meeting_file_data_lillyglobal_by_program($program_name);

  foreach ($data_lillyform as $key => $value) {
    $result[$value[20]] = $data_lillyglobal[$key][20];
  }

  $output = NULL;
  if (is_array($result)) {
    foreach ($result as $key => $value) {
      dpm($key . ' => ' . $value . ',') ;
    }
  }

  // print_r($output);
}
/** - - - - - - import data - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

/**
 *
  require_once(DRUPAL_ROOT . '/sites/all/modules/custom/phpdebug/import_export_node.php');
  require_once(DRUPAL_ROOT . '/sites/all/modules/custom/phpdebug/meeting_file.php');
  run_import_meeting();
 */
function run_import_meeting() {
  $data = meeting_file_data_lillyform();

  // change some value
  foreach($data as $key => $row) {
    if ($key > -1 && $key < 1000) {
      _convert_data($row, $key);
    }
  }
}

/**
 * convert data to tid
 */
function _convert_data($row = array(), $key = NULL) {
  $result = array();
  // programName
  if ($row[0]) {
    $terms = taxonomy_get_term_by_name($row[0], 'program');
    if (count($terms) == 1) {
      $result[0] = key($terms);
    }
    else {
      dpm($key . '-- wrong $row[1]');
      return;
    }
  }
  else {
    dpm($key . '-- no $row[0]');
  }

  // multiTherapeuticEvent
  if ($row[1]) {
    $terms = taxonomy_get_term_by_name($row[1], 'multi_therapeutic_event');
    if (count($terms) == 1) {
      $result[1] = key($terms);
    }
    else {
      dpm($key . '-- wrong $row[1]');
      return;
    }
  }
  else {
    dpm($key . '-- no $row[1]');
  }

  // meetingFormatName
  if ($row[2]) {
    $terms = taxonomy_get_term_by_name($row[2], 'meeting_format');
    if (count($terms) == 1) {
      $result[2] = key($terms);
    }
    else {
      dpm($key . '-- wrong $row[2]');
      return;
    }
  }
  else {
    dpm($key . '-- no $row[2]');
  }

  // userGroupName
  if ($row[3]) {
    $terms = taxonomy_get_term_by_name($row[3], 'user_group');
    if (count($terms) == 1) {
      $result[3] = key($terms);
    }
    else {
      dpm($key . '-- wrong $row[3]');
      return;
    }
  }
  else {
    dpm($key . '-- no $row[3]');
  }

  // repName
  $result[4] = $row[4];
  if ($row[4]) {
    $user = user_load_by_name($row[4]);
    $user_id = $user->uid;
    if (isset($user->uid)) {
      $result[4] = $user->uid;
    }
    else {
      dpm($key . '-- wrong $row[4]');
      return;
    }
  }
  else {
    dpm($key . '-- no $row[4]');
  }

  // speakerName
  $result[5] = $row[5];
  if ($row[5]) {
    $user = user_load_by_name($row[5]);
    $user_id = $user->uid;
    if (isset($user->uid)) {
      $result[5] = $user->uid;
    }
    else {
      dpm($key . '-- wrong $row[5]');
      return;
    }
  }
  else {
    dpm($key . '-- no $row[5]');
  }

  // dateTimeStamp
  if ($row[6]) {
    $result[6] = $row[6];
  }
  else {
    dpm($key . '-- no $row[6]');
  }

  // meetingLocation ****
  if ($row[7]) {
    $terms = taxonomy_get_term_by_name($row[7], 'meeting_location');
    if (count($terms) == 1) {
      $result[7] = key($terms);
    }
    else {
      dpm($key . '-- wrong $row[7]');
      return;
    }
  }
  else {
    dpm($key . '-- no $row[7]');
  }

  $result[8] = $row[8];
  // venueName
  if ($row[8]) {
  }
  else {
    dpm($key . '-- no $row[8]');
  }

  // meetingAddress
  $result[9] = $row[9];
  if ($row[9]) {
  }
  else {
    dpm($key . '-- no $row[9]');
  }

  // provinceName
  if ($row[10]) {
    $terms = taxonomy_get_term_by_name($row[10], 'province');
    if (count($terms) == 1) {
      $result[10] = key($terms);
    }
    else {
      dpm($key . '-- wrong $row[10]');
      return;
    }
  }
  else {
    dpm($key . '-- no $row[10]');
  }

  // cityName
  if ($row[11]) {
    $city_terms = taxonomy_get_term_by_name($row[11], 'city');
    if (count($city_terms) == 1) {
      $result[11] = key($city_terms);
    }
    elseif(count($city_terms) > 1) {
      if (is_array($city_terms)) {
        foreach ($city_terms as $city) {
          if (isset($city->field_city_province['und'][0]['target_id'])) {
            if($city->field_city_province['und'][0]['target_id'] == $result[10]) {
              $result[11] = $city->tid;
            }
          }
        }
      }
    }
    else {
      dpm($key . '-- wrong $row[11]');
      return;
    }
  }
  else {
    dpm($key . '-- no $row[11]');
  }

  // meetingPostalCode
  $result[12] = $row[12];
  $result[13] = $row[13];
  $result[14] = $row[14];
  $result[15] = $row[15];
  $result[16] = $row[16];
  $result[18] = $row[18];
  $result[19] = $row[19];

  // received
  if ($row[17]) {
    $terms = taxonomy_get_term_by_name($row[17], 'meeting_received');
    if (count($terms) == 1) {
      $result[17] = key($terms);
    }
    else {
      dpm($key . '-- wrong $row[17]');
      return;
    }
  }
  else {
    dpm($key . '-- no $row[17]');
  }

  // create node
  if ($key > -1) {
    // _entity_create_node($result, $key);
  }
}

/**
 *
 */
function _entity_create_node($row = array(), $key = NULL) {
  global $user;

  // creating a new object $node and setting its 'type' and uid property
  $values = array(
    'type' => 'meeting',
    'uid' => $user->uid,
    'status' => 1,
    'promote' => 0,
  );
  $entity = entity_create('node', $values);

  // Using the wrapper
  $node_wrapper = entity_metadata_wrapper('node', $entity);

  $node_wrapper->title->set('Migration Lilly Meeting');

  $node_wrapper->field_meeting_program->set(intval($row[0])); // programName
  $node_wrapper->field_meeting_multi_therape->set(intval($row[1])); // multiTherapeuticEvent
  $node_wrapper->field_meeting_meeting_format->set(intval($row[2])); // meetingFormatName
  $node_wrapper->field_meeting_user_group->set(intval($row[3])); // userGroupName

  if ($row[4]) {
    $node_wrapper->field_meeting_representative->set(intval($row[4])); // repName
  }
  if ($row[5]) {
    $node_wrapper->field_meeting_speaker->set(intval($row[5])); // speakerName
  }
  $node_wrapper->field_meeting_date->set(intval($row[6])); // dateTimeStamp
  $node_wrapper->field_meeting_location->set(intval($row[7])); // meetingLocation
  $node_wrapper->field_meeting_venue_name->set($row[8]); // venueName
  $node_wrapper->field_meeting_address->set($row[9]); // meetingAddress
  $node_wrapper->field_meeting_province->set(intval($row[10])); // provinceName
  $node_wrapper->field_meeting_city->set(intval($row[11])); // cityName

  if ($row[12]) {
    $node_wrapper->field_meeting_postal_code->set($row[12]); // meetingPostalCode
  }
  if ($row[13]) {
    $node_wrapper->field_meeting_honorarium->set($row[13]); // honorarium
  }
  if ($row[14]) {
    $node_wrapper->field_meeting_food_cost->set($row[14]); // foodCost
  }
  if ($row[15]) {
    $node_wrapper->field_meeting_catering->set($row[15]); // catering
  }
  if ($row[16]) {
    $node_wrapper->field_meeting_signatures->set($row[16]); // signaturesNum
  }
  if ($row[17]) {
    $node_wrapper->field_meeting_received->set($row[17]); // received
  }
  if ($row[18]) {
    $node_wrapper->field_meeting_latlon_lat->set($row[18]); // meetingLat
  }
  if ($row[19]) {
    $node_wrapper->field_meeting_latlon_lon->set($row[19]); // meetingLon
  }

  $node_wrapper->save();
  dpm($entity->nid . ' -- ' . $key);
}

/** - - - - - - convert data - - - - - - - - - - - - - - - - - - - - - - - - - -  */

