<?php
// $Id$

/**
 * @file
 * Implements Views module hooks.
 */

/**
 * Implements hook_views_data().
 */
function paypaad_ui_views_data() {
  $data = array();

  // Introducing {paypaad} table.
  $data['paypaad']['table']['group'] = t('Paypaad transaction');

  $data['paypaad']['table']['base'] = array(
    'field' => 'pid',
    'title' => t('Paypaad transaction'),
    'help'  => t('Payment transactions information processed through Paypaad gateway.'),
  );

  $data['paypaad']['table']['join'] = array(
    'users' => array(
      'left_table' => 'paypaad',
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  $data['paypaad']['pid'] = array(
    'title' => t('Transaction identifier'),
    'help'  => t('The Paypaad transaction ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['paypaad']['uid'] = array(
    'title' => t('User identifier'),
    'help'  => t('User ID of who the transaction performed by.'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name',
    ),
    'filter' => array(
      'title' => t('Name'),
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'label' => t('user'),
    ),
  );

  $data['paypaad']['transaction_reference_id'] = array(
    'title' => t('Transaction ref. identifier'),
    'help'  => t('Reference ID of transaction, also known as tref in Paypaad talk.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['invoice_number'] = array(
    'title' => t('Invoice number'),
    'help'  => t('Paypaad transaction invoice number as returned by the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['invoice_date'] = array(
    'title' => t('Invoice date'),
    'help'  => t('Paypaad transaction invoice date as returned by the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['trace_number'] = array(
    'title' => t('Trace number'),
    'help'  => t('Paypaad transaction trace number as returned by the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['reference_number'] = array(
    'title' => t('Ref. number'),
    'help'  => t('Paypaad transaction reference number as returned by the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['transaction_date'] = array(
    'title' => t('Transaction GMT date'),
    'help'  => t('Paypaad transaction GMT date as returned by the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['amount'] = array(
    'title' => t('Transaction amount'),
    'help'  => t('Transaction amount paid by the customer.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['module_id'] = array(
    'title' => t('Module identifier'),
    'help'  => t('Payment handler module ID.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['entity_id'] = array(
    'title' => t('Entity identifier'),
    'help'  => t('Drupal entity ID, might be a node, UC order, etc.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['paypaad']['timestamp'] = array(
    'title' => t('Record date'),
    'help'  => t('The date in which the transaction information has been recorded.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}

