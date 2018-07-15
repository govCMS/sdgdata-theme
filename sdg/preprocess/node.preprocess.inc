<?php
/**
 * @file
 * Preprocessors for nodes.
 */

/**
 * Implements template_preprocess_node.
 */
function sdg_preprocess_node(&$variables) {
  $elements = $variables['elements'];
  $content = &$variables['content'];
  $node = entity_metadata_wrapper('node', $variables['node']);

  $hook = __FUNCTION__ . "__{$elements['#bundle']}__{$elements['#view_mode']}";

  if (is_callable($hook)) {
    $hook($variables);
  }

  if ($elements['#bundle'] == 'indicator' && $elements['#view_mode'] == 'full') {
    $theme_path = drupal_get_path('theme', 'sdg');
    $responsive_tabs_path = $theme_path . '/libraries/Easy-Responsive-Tabs-to-Accordion';

    drupal_add_js($responsive_tabs_path . '/js/easyResponsiveTabs.js');

    drupal_add_js($theme_path . '/js/sdg.responsive-tabs.js');

    // Duplicate the indicator status field and render as a themed button above
    // the caveat.
    if (isset($content['caveat_intro_text']) && isset($node->field_indicator_status)) {
      $indicator_status = array(
        '#theme' => 'sdg_indicator_status',
        '#indicator' => $node->field_indicator_status->value(),
      );
      $content['caveat_intro_text']['#prefix'] = render($indicator_status);
    }
  }

  if (isset($variables['content']['field_data_sources'])) {
    $count = 1;
    $data_sources = &$variables['content']['field_data_sources'];

    // Loop through all the data sources on the indicators.
    foreach (element_children($data_sources) as $delta) {
      $paragraphs = &$data_sources[$delta]['entity']['paragraphs_item'];
      foreach (element_children($paragraphs) as $paragraph_delta) {
        $paragraph = $paragraphs[$paragraph_delta]['#entity'];

        // Remove content if archived.
        if ($paragraph->field_archived[LANGUAGE_NONE][0]['value']) {
          unset($variables['content']['field_data_sources'][$delta]);
          continue;
        }

        // Add the source delta for output on the paragraph template.
        $paragraphs[$paragraph_delta]['#entity']->delta = $count;
        $count++;
      }
    }
  }

  $node_bundle = $node->getBundle();

  if (empty($variables['content']['field_other_info_indicator']) && $node_bundle != 'webform') {
    $variables['content']['field_other_info_indicator'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('view-empty')),
      'message' => array(
        '#theme' => 'html_tag',
        '#tag' => 'p',
        '#value' => t('No other information for this indicator'),
      ),
    );
  }
}

/**
 * Implements template_preprocess_node__BUNDLE__VIEW-MODE().
 *
 * Adds the Indicator Status modifier to the node template to ease theming.
 */
function sdg_preprocess_node__indicator__teaser(&$variables) {
  if (empty($variables['field_indicator_status'])) {
    return;
  }

  $status = $variables['field_indicator_status'][0]['taxonomy_term'];
  $status_wrapper = entity_metadata_wrapper('taxonomy_term', $status);

  try {
    $variables['classes_array'] = array('indicator-teaser');
    $variables['classes_array'][] = 'indicator-teaser--' . mb_strtolower($status_wrapper->field_machine_name->value());
  }
  catch (EntityMetadataWrapperException $e) {
    watchdog('sdg', 'EntityMetadataWrapper exception in %function() <pre>@trace</pre>', array(
      '%function' => __FUNCTION__,
      '@trace' => $e->getTraceAsString(),
    ), WATCHDOG_ERROR);
  }
}
