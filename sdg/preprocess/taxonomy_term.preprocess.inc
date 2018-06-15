<?php
/**
 * @file
 * Preprocessors for taxonomy_term.
 */

/**
 * Implements template_taxonomy_term().
 */
function sdg_preprocess_taxonomy_term(&$vars) {

  // If goal term.
  if ('goals' == $vars['vocabulary_machine_name']) {

    if (!empty($vars['field_number'][LANGUAGE_NONE])) {
      // Build title.
      $vars['goal_name'] = t('Goal @num @name', array(
        '@num' => $vars['field_number'][LANGUAGE_NONE][0]['value'],
        '@name' => $vars['name'],
      ));
    }

    if (!empty($vars['field_machine_name'][LANGUAGE_NONE])) {
      // Build machine name.
      $vars['machine_name'] = $vars['field_machine_name'][LANGUAGE_NONE][0]['value'];
    }

    // Build icon code into an image tag.
    $icon_path = path_to_theme() . '/images/goal-icons/goal-' . $vars['field_icon_name'][0]['value'] . '.svg';
    $vars['content']['field_icon_name'][0]['#markup'] = file_get_contents($icon_path);
  }

  // Check to see we're rendering a target term 'inline'.
  // e.g. for indicator nodes.
  if ($vars['vocabulary_machine_name'] == 'target' && $vars['view_mode'] == 'inline_teaser') {
    // Generate the label markup and add any closing tags.
    $vars['content']['description']['#prefix'] .= t('<div class="label-inline">Target name</div><div>');
    $vars['content']['description']['#suffix'] .= '</div>';
  }

}
