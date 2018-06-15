<?php

/**
 * @file
 * Includes taxonomy term helpers.
 */

define('SDG_GOAL_VID', 2);

/**
 * Helper function to get indicators by goal.
 *
 * @param int $id
 *   The Goal TID.
 *
 * @return array
 *   Total number of indicators per goal and a breakdown of the indicators.
 */
function sdg_term_find_indicators_by_goal_id($id) {
  $indicators = sdg_term_get_indicator_status_terms();
  $indicator_count_link = '';

  // Abort operation if no indicators are found.
  if (!$indicators) {
    return array();
  }

  // Load all available indicators.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'indicator')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_goal', 'tid', $id, '=')
    ->addMetaData('account', user_load(1));

  $result = $query->execute();

  // Parse indicators into their percentage breakdowns.
  $total = 0;
  if (isset($result['node'])) {

    foreach (array_keys($result['node']) as $nid) {
      $indicator = entity_metadata_wrapper('node', $nid);
      $label = strtolower($indicator->field_indicator_status->label());

      $indicators[$label]['count']++;
      $total++;
    }
  }

  // Sort by weight.
  uasort($indicators, 'drupal_sort_weight');

  // If the count of indicators is not zero convert into a percentage.
  if ($total) {
    array_walk($indicators, function (&$indicator) use ($total) {
      $indicator['percent'] = round(($indicator['count'] / $total) * 100);
    });

    $count = format_plural($total, '@count indicator', '@count indicators');
    $indicator_count_link = l($count, 'taxonomy/term/' . $id);
  }

  return compact('indicators', 'indicator_count_link');
}

/**
 * Get all indicator status terms.
 *
 * @return array
 *   Returns a list of valid indicator status to output as a list/graph on
 *   the 'Report Status' page.
 */
function sdg_term_get_indicator_status_terms() {
  $result = sdg_term_get_indicator_status_terms_load();

  // Abort if not results found.
  if (!isset($result['taxonomy_term'])) {
    return array();
  }

  $terms = taxonomy_term_load_multiple(array_keys($result['taxonomy_term']));

  // Set weight correctly.
  $i = 0;
  foreach ($terms as &$term) {
    $term->weight = $i;
    $i++;
  }

  // Build the indicator keys, lowered to allow better matching.
  $keys = array_map(function ($term) {
    return strtolower($term->name);
  }, $terms);

  // Build the default values that will be displayed on the page.
  $values = array_map(function ($term) {
    return array(
      'count' => 0,
      'percent' => 0,
      'label' => $term->name,
      'class' => $term->field_machine_name[LANGUAGE_NONE][0]['value'],
      'weight' => $term->weight,
    );
  }, $terms);

  return array_combine($keys, $values);
}


/**
 * Load indicator status terms, without ignored status.
 *
 * @return array
 *   Returns an array of terms if found.
 */
function sdg_term_get_indicator_status_terms_load() {
  $vocab = taxonomy_vocabulary_machine_name_load('indicator_status');

  // Get the indicator terms excluding the ignored status.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term')
    ->propertyCondition('vid', $vocab->vid)
    ->propertyOrderBy('weight', 'ASC')
    ->addMetaData('account', user_load(1));

  return $query->execute();
}

/**
 * Get the goal ID that applies to current page.
 *
 * @return int|null
 *   TID or empty.
 */
function sdg_term_get_goal_tid_for_current_page() {
  $term = menu_get_object('taxonomy_term', 2);
  if (!empty($term) && !empty($term->vid) && $term->vid == SDG_GOAL_VID) {
    return $term->tid;
  }
  $node = menu_get_object();
  if (!empty($node) && !empty($node->type) && $node->type == 'indicator' && !empty($node->field_goal[LANGUAGE_NONE])) {
    return $node->field_goal[LANGUAGE_NONE][0]['tid'];
  }
  return '';
}
