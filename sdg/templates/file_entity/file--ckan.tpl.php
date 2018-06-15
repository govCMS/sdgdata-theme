<?php

/**
 * @file
 * Default theme implementation to display a file.
 *
 * This template has been overriden to print the file label and wrap it in a
 * <h3> tag.
 */
?>
<div id="<?php print $id; ?>" class="<?php print $classes ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h3><?php print $label; ?></h3>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
    // We hide the links now so that we can render them later.
    hide($content['links']);
    // Check to see if the file has an external url for linking.
    if(!empty($content['file']['#file']->external_url)) {;?>
      <a href="<?php print render($content['file']['#file']->external_url);?>"><?php print render($content);?></a>
      <?php
    } else {
      print render($content);
    }
    ?>
  </div>

  <?php print render($content['links']); ?>

</div>
