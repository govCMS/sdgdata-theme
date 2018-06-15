<?php

/**
 * @file
 * Alters for Views exposed forms.
 */

/**
 * Implements hook_form_views_exposed_form_alter().
 *
 * Alters views_exposed_form_alter__VIEW_NAME__DISPLAY_NAME.
 */
function sdg_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
  $view = $form_state['view'];
  $hook = __FUNCTION__ . "__{$view->name}__{$view->current_display}";

  if (is_callable($hook)) {
    $hook($form, $form_state, $form_id);
  }
}

/**
 * Implements hook_form_views_exposed_form_alter().
 *
 * Populates the Reporting Agency field filter for Indicators search View.
 */
function sdg_form_views_exposed_form_alter__indicator_search__page(&$form, &$form_state, $form_id) {
  // Prepend Goal filter with 'Goal @number'.
  if (!empty($form['goal'])) {
    $goal_tids = array_filter(array_keys($form['goal']['#options']), 'is_numeric');
    $goals = entity_load('taxonomy_term', $goal_tids);

    foreach ($goals as $goal) {
      try {
        $goal_wrapper = entity_metadata_wrapper('taxonomy_term', $goal);
        $form['goal']['#options'][$goal->tid] = t('Goal @number @name', array(
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
    }

    asort($form['goal']['#options'], SORT_NATURAL);
  }

  // Pre-populate Responsible Agency filter with Australian agencies.
  if (!empty($form['reporting_agency'])) {
    $form['reporting_agency'] = array(
      '#type' => 'select',
      '#options' => sdg_node_agency_options_list(),
      '#empty_option' => t('- Any -'),
      '#empty_value' => 'All',
    );
  }

  // We don't have access to the filter labels here, so unfortunately we need
  // to redefine them.
  $filters = array(
    'keyword' => t('Keyword'),
    'indicator_status' => t('Status'),
    'goal' => t('Goal'),
    'reporting_agency' => t('Responsible Agency'),
    'year' => t('Year'),
    'un_designated_tier' => t('UN designated tier'),
  );

  // Add placeholders that match the filter labels.
  foreach (element_children($form) as $element_key) {
    if (!array_key_exists($element_key, $filters)) {
      continue;
    }

    $element = &$form[$element_key];
    $element_label = $filters[$element_key];

    switch ($element['#type']) {
      case 'textfield':
        $element['#attributes']['placeholder'] = $element_label;
        break;

      case 'select':
        $element['#empty_option'] = $element_label;
        $element['#empty_value'] = 'All';
        break;
    }
  }
}
