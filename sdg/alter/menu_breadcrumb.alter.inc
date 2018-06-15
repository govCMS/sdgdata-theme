<?php

/**
 * @file
 * Alters for menu breadcrumb.
 */

/**
 * Implements hook_menu_breadcrumb_alter().
 */
function sdg_menu_breadcrumb_alter(&$active_trail, $item) {
  if ($item['path'] === 'node/%') {
    $node = reset($item['page_arguments']);
    $hook = __FUNCTION__ . "__node__{$node->type}";
  }

  if ($item['path'] === 'taxonomy/term/%') {
    $taxonomy_term = reset($item['page_arguments']);
    $taxonomy_vocab = taxonomy_vocabulary_load($taxonomy_term->vid);
    $hook = __FUNCTION__ . "__taxonomy_term__{$taxonomy_vocab->machine_name}";
  }

  if (isset($hook) && is_callable($hook)) {
    $hook($active_trail, $item);
  }
}

/**
 * Implements hook_menu_breadcrumb_alter__ENTITY_TYPE__BUNDLE().
 *
 * Overrides the breadcrumbs for Indicator nodes.
 */
function sdg_menu_breadcrumb_alter__node__indicator(&$active_trail, $item) {
  $home_path = variable_get('site_frontpage', 'indicator');
  $home_item = menu_get_item($home_path);
  $home_item['title'] = t('Home');

  $indicator = reset($item['page_arguments']);
  $indicator_item = menu_get_item('node/' . $indicator->nid);
  $indicator_wrapper = entity_metadata_wrapper('node', $indicator);

  try {
    $goal = $indicator_wrapper->field_goal->value();
    $goal_wrapper = entity_metadata_wrapper('taxonomy_term', $goal);
    $goal_item = menu_get_item('taxonomy/term/' . $goal->tid);
    $goal_item['title'] = t('Goal @number @name', array(
      '@number' => $goal_wrapper->field_number->value(),
      '@name' => $goal_wrapper->label(),
    ));
  }
  catch (EntityMetadataWrapperException $e) {
    watchdog('sdg', 'EntityMetadataWrapper exception in %function() <pre>@trace</pre>', array(
      '%function' => __FUNCTION__,
      '@trace' => $e->getTraceAsString(),
    ), WATCHDOG_ERROR);
  }

  if (isset($home_item) && isset($goal_item) && isset($indicator_item)) {
    $active_trail = array($home_item, $goal_item, $indicator_item);
  }
}

/**
 * Implements hook_menu_breadcrumb_alter__ENTITY_TYPE__BUNDLE().
 *
 * Overrides the breadcrumbs for Goal taxonomy terms.
 */
function sdg_menu_breadcrumb_alter__taxonomy_term__goals(&$active_trail, $item) {
  $home_path = variable_get('site_frontpage', 'indicator');
  $home_item = menu_get_item($home_path);
  $home_item['title'] = t('Home');

  $goal = reset($item['page_arguments']);
  $goal_item = menu_get_item('taxonomy/term/' . $goal->tid);
  $goal_wrapper = entity_metadata_wrapper('taxonomy_term', $goal);

  try {
    $goal_item['title'] = t('Goal @number @name', array(
      '@number' => $goal_wrapper->field_number->value(),
      '@name' => $goal_wrapper->label(),
    ));
  }
  catch (EntityMetadataWrapperException $e) {
    watchdog('sdg', 'EntityMetadataWrapper exception in %function() <pre>@trace</pre>', array(
      '%function' => __FUNCTION__,
      '@trace' => $e->getTraceAsString(),
    ), WATCHDOG_ERROR);
  }

  if (isset($home_item) && isset($goal_item)) {
    $active_trail = array($home_item, $goal_item);
  }
}
