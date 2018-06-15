<?php
/**
 * @file
 * Preprocessors for entities.
 */

/**
 * Implements template_preprocess_entity().
 *
 * Preprocess views_view_fields__ENTITY_TYPE.
 */
function sdg_preprocess_entity(&$vars) {
  $hook = __FUNCTION__ . "__{$vars['elements']['#entity_type']}";

  if (is_callable($hook)) {
    $hook($vars);
  }
}

/**
 * Implements template_preprocess_entity().
 *
 * Add source number to data sources paragraphs.
 */
function sdg_preprocess_entity__paragraphs_item(&$vars) {
  $paragraph = $vars['elements']['#entity'];

  if ($paragraph->field_name != 'field_data_sources') {
    return;
  }

  foreach ($vars['content'] as &$element) {
    if (isset($element['#label_display'])) {
      $element['#label_display'] = 'hidden';
    }
  }

  $vars['delta'] = $paragraph->delta;
}
