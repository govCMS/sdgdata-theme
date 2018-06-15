<?php

/**
 * @file
 * Sustainable Development Goals Admin template.php file.
 */

/**
 * Implements hook_form_BASE_FORM_ID_alter().
 *
 * Group the Indicator Status Caveat field options.
 */
function sdg_admin_form_indicator_node_form_alter(&$form, &$form_state, $form_id) {
  if (empty($form['field_indicator_status_caveat'][LANGUAGE_NONE]['#options'])) {
    return;
  }

  $groups = array(
    0 => 'Other',
    3 => 'Reported',
    2 => 'Exploring data sources',
    1 => 'Not yet reported',
    4 => 'Not applicable',
  );

  $grouped_options = drupal_map_assoc($groups, function () {
    return array();
  });

  $options = &$form['field_indicator_status_caveat']['und']['#options'];

  foreach ($options as $option_key => $option_value) {
    $group_key = substr($option_key, 0, 1);
    $group_name = array_key_exists($group_key, $groups) ? $groups[$group_key] : $groups[0];
    $grouped_options[$group_name][$option_key] = $option_value;
  }

  $options = array_filter($grouped_options);

  if (isset($form['field_goal'][LANGUAGE_NONE]['#options'])) {
    _sdg_admin_enhance_goal_option_titles($form['field_goal'][LANGUAGE_NONE]['#options']);
  }

  $form['title']['#description'] = t("Use the word 'Indicator' and the 3 digit indicator number e.g. Indicator 6.1.1");
}

/**
 * Updates the goal dropdown to have more descriptive text values.
 */
function _sdg_admin_enhance_goal_option_titles(&$form) {
  // Update the option values to include number and name.
  foreach (sdg_admin_goal_name_load() as $goal_id) {
    $wrapper = entity_metadata_wrapper('taxonomy_term', $goal_id);
    $replacements = array(
      '@number' => $wrapper->field_number->value(),
      '@name' => $wrapper->label(),
    );
    $form[$goal_id] = t('goal @number @name', $replacements);
  }
}


/**
 * Load goal terms.
 *
 * @return array
 *   Returns an array of terms if found.
 */
function sdg_admin_goal_name_load() {
  $vocab = taxonomy_vocabulary_machine_name_load('goals');

  // Get the indicator terms excluding the ignored status.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term')
    ->propertyCondition('vid', $vocab->vid)
    ->addMetaData('account', user_load(1));

  $results = $query->execute();

  return isset($results['taxonomy_term']) ? array_keys($results['taxonomy_term']) : array();
}
