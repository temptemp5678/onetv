<?php

/**
 * print one vocabulary
 */
$tree = taxonomy_get_tree(6);
$output = '';

foreach($tree as $key => $val){
  $TermCityInfo = new TermCityInfo($val->tid);

  $row = '';
  if ($TermCityInfo) {
    if ($TermCityInfo->tid > 2000) {
      $row = array(
        '"' . $TermCityInfo->termName() . '"',    // some string output
        $TermCityInfo->provinceName(),
        $TermCityInfo->latitude(),
        $TermCityInfo->longitude(),
      );

      print_r('array(' . implode(',', $row) . '),');
      // $output[] = implode(',', $row);
      // $output[] = $row;
    }
  }
}

/** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
$terms = termsArray();
foreach($terms as $key => $value){
  $data = array(
    'name' => $value,
    'vid' => 5,
  );
  $term = entity_create('taxonomy_term', $data);

  $wrapper = entity_metadata_wrapper('taxonomy_term', $term);
  $wrapper->save();

  // save again
  $wrapper->save();
}

/**
 * import terms
 */
function termsArray() {
  $terms = array(
    'Administrative',
    'Business',
    'Computer Sciences',
    'Consumer Packaged Goods',
    'Consumer Products',
    'Customer Service',
    'Financial Services and Banking',
    'Healthcare and Medical Services',
    'Hospitality',
    'Maintenance',
    'Manufacturing',
    'Marketing',
    'Pharmacy',
    'Recruitment and Staffing',
    'Retail',
    'Project Management',
    'IT',
    'Sales',
    'Telecommunications',
  );

  return $terms;
}

/** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

$citys = cityArray();
foreach($citys as $key => $value){
  $data = array(
    'name' => $value[0],
    'vid' => 18,
  );
  $term = entity_create('taxonomy_term', $data);

  $wrapper = entity_metadata_wrapper('taxonomy_term', $term);
  $wrapper->save();

  // Note that the entity id (e.g., nid) must be passed as an integer not a string
  $wrapper->field_city_province->set(intval($value[1]));
  // set some customer field value
  $wrapper->field_city_latlon_lat->set($value[2]);
  $wrapper->field_city_latlon_lon->set($value[3]);
  // save again
  $wrapper->save();
}

/**
 * import citys data
 */
function cityArray() {
  $citys = array(
    array("Addington",22,46.195426000000,-73.620458000000),
    array("Yellowknife",24,62.453971700000,-114.371788600000),
    array("York",27,43.695678700000,-79.450354400000),
    array("Yorkton",30,51.213889000000,-102.462778000000),
    array("Zorra",27,43.163405400000,-80.942891100000),
  );

  return $citys;
}
