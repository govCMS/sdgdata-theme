<?php

/**
 * @file
 * Preprocessor for views_view_fields.
 */

/**
 * Implements template_preprocess_views_view_fields().
 *
 * Preprocess views_view_fields__VIEW_NAME.
 */
function sdg_preprocess_views_view_fields(&$vars) {
  $hook = __FUNCTION__ . "__{$vars['view']->name}";

  if (is_callable($hook)) {
    $hook($vars);
  }
}

/**
 * Implements template_preprocess_views_view_fields().
 *
 * Merge indicators of the goal into the template variables.
 */
function sdg_preprocess_views_view_fields__reporting_status_by_goal(&$vars) {
  $view = $vars['view'];

  if ($view->current_display == 'panel_pane_1') {
    $vars = array_merge($vars, sdg_term_find_indicators_by_goal_id($vars['row']->tid));
  }
}

/**
 * Implements template_preprocess_views_view_fields().
 *
 * Create excerpts for search results if they aren't present.
 */
function sdg_preprocess_views_view_fields__indicator_search(&$vars) {
  if (!empty($vars['fields']['search_api_excerpt'])) {
    // If Search API was able to build an excerpt skip this and just display
    // what was return by search api.
    return;
  }

  // Try and find the entity.
  $entity = FALSE;

  if (isset($vars['row']->entity) && is_object($vars['row']->entity)) {
    $entity = $vars['row']->entity;
  }

  if (!$entity && isset($vars['row']->_entity_properties['entity object'])) {
    $entity = $vars['row']->_entity_properties['entity object'];
  }

  if (!$entity) {
    // If the entity couldn't be found... we're out of luck.
    return;
  }

  // Render the default view mode.
  $entity_view = entity_view('node', array($entity));

  if (empty($entity->nid) || empty($entity_view['node'][$entity->nid])) {
    return;
  }

  // Clean up the view mode.
  $entity_view = $entity_view['node'][$entity->nid];

  // Remove the unnecessary items from the render array.
  unset($entity_view['title']);
  unset($entity_view['links']);
  unset($entity_view['#contextual_links']);

  // Clean up the entity markup.
  $entity_view = drupal_render($entity_view);
  $entity_view = sdg_strip_tags($entity_view);
  $entity_view = sdg_text_trim($entity_view);

  $render_array = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('field-content'),
    ),
    'content' => array(
      '#theme' => 'html_tag',
      '#tag' => 'p',
      '#value' => $entity_view,
    ),
  );

  $vars['fields']['view_node']->content = drupal_render($render_array) . $vars['fields']['view_node']->content;
}

/**
 * Implements template_preprocess_views_view_fields().
 *
 * Adds percentage to the overall reporting status.
 */
function sdg_preprocess_views_view_fields__indicator_status_graph(&$vars) {
  $view = $vars['view'];
  if ($view->current_display == 'panel_pane_1') {
    $row = $vars['row'];
    $vars['percentage'] = _sdg_calculate_indicator_status_graph_percentage($row, $view);
  }
}

/**
 * Calculate indicator status graph percentage.
 *
 * @param object $row
 *   The view result row.
 * @param object $view
 *   Actual view.
 *
 * @return float
 *   Calculated percentage.
 */
function _sdg_calculate_indicator_status_graph_percentage($row, $view) {
  // Total the count of indicators.
  $total = array_sum(array_map(function ($point) {
    return $point->field_indicator_status_taxonomy_term_data_nid;
  }, $view->result));

  // Calculate the percentage.
  return round($row->field_indicator_status_taxonomy_term_data_nid / $total * 100, 1);
}

/**
 * Custom helper function to return the default hero image.
 */
function _sdg_view_hero_default_img() {
  // Show the default indicator hero.
  $img_path = '/' . drupal_get_path('theme', 'sdg') . '/images/default-hero.jpg';
  $img = '<img src="' . $img_path . '" style="display: none;">';

  return $img;
}

/**
 * Implements template_preprocess_views_view_fields().
 *
 * Show a default hero image for Indicators.
 */
function sdg_preprocess_views_view_fields__indicator_hero(&$vars) {
  foreach ($vars['fields'] as $id => $field) {
    if ($id == 'field_image' && empty($vars['row']->field_field_image)) {
      $field->content = _sdg_view_hero_default_img();
    }

    $vars[$id] = $field->wrapper_prefix . $field->content . $field->wrapper_suffix;
  }
}

/**
 * Implements template_preprocess_views_view_fields().
 *
 * Show a default hero image for Indicators.
 */
function sdg_preprocess_views_view_fields__goals_hero(&$vars) {
  foreach ($vars['fields'] as $id => $field) {
    if ($id == 'field_image' && empty($vars['row']->field_field_image)) {
      $field->content = _sdg_view_hero_default_img();
    }

    $vars[$id] = $field->wrapper_prefix . $field->content . $field->wrapper_suffix;
  }
}
