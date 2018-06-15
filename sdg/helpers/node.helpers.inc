<?php

/**
 * @file
 * Node helpers.
 */

/**
 * The unique identifier of the international applicable agency.
 */
define('SDG_NODE_AGENCY_REGION_INTERNATIONAL', 1);

/**
 * The unique identifier of the national applicable agency.
 */
define('SDG_NODE_AGENCY_REGION_AUSTRALIA', 2);

/**
 * Helper to return a list of Agency node options sorted alphabetically.
 *
 * @param int $applicable_region
 *   (optional) The applicable region.
 * @param int $start
 *   (optional) The first entity from the result set to return. If NULL, removes
 *   any range directives that are set.
 * @param int $length
 *   (optional) The number of entities to return from the result set.
 *
 * @return array
 *   An associative array where the keys are nids and values are titles.
 */
function sdg_node_agency_options_list($applicable_region = SDG_NODE_AGENCY_REGION_AUSTRALIA, $start = 0, $length = 100) {
  $options = array();

  $query = new EntityFieldQuery();
  $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'agency')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_applicable_region', 'value', $applicable_region, '=')
    ->propertyOrderBy('title')
    ->range($start, $length);

  $result = $query->execute();

  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
    $nodes = entity_load('node', $nids);

    foreach ($nodes as $node) {
      $options[$node->nid] = $node->title;
    }
  }

  return $options;
}
