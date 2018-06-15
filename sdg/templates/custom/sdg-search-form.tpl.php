<?php
/**
 * @file
 * Search form template.
 */
?>

<form action="<?php print url('search'); ?>" method="get" id="search-form" class="search-form">
  <div class="search-form__item">
    <label for="edit-keyword" class="search-form__label element-hidden">Keywords</label>
    <input type="text" id="edit-keyword" name="keyword" value="" placeholder="Enter your keywords..." class="search-form__widget" />
  </div>
  <div class="search-form__actions">
    <button type="submit" id="edit-submit-search-form" name="" class="search-form__action search-form__toggle">
      <i class="fa-icon-search"></i><span class="element-hidden">Search</span>
    </button>
  </div>
</form>
