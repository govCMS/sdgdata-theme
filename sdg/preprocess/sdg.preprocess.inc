<?php
/**
 * @file
 * Preprocessors for custom sdg theme hooks.
 */

/**
 * Implements hook_preprocess_sdg_indicator_status().
 */
function sdg_preprocess_sdg_indicator_status(&$variables) {
  // Load the status and machine name.
  $indicator_status = entity_metadata_wrapper('taxonomy_term', $variables['indicator']);
  $machine_name = $indicator_status->field_machine_name->value();

  // Populate template vars.
  $variables['title'] = $indicator_status->name->value();
  $variables['background_class'] = 'status--' . $machine_name . '--background';
  $variables['link'] = url('search', array(
    'query' => array('indicator_status' => $indicator_status->tid->value()),
  ));

}
