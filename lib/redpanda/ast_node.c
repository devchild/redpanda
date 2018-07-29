#include <ast_node.h>

/* Private structure definition. */
typedef struct {
  gchar *text;
  /* stuff */
} AstNodePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (AstNode, ast_node, G_TYPE_OBJECT)

enum
{
  PROP_TEXT = 1,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static void
ast_node_set_property (GObject      *object,
                          guint         property_id,
                          const GValue *value,
                          GParamSpec   *pspec)
{
  AstNode *self = AST_NODE (object);
  AstNodePrivate *priv = ast_node_get_instance_private(self); 
  switch (property_id)
    {
    case PROP_TEXT:
      g_free (priv->text);
      priv->text = g_value_dup_string (value);
      break;

    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
ast_node_get_property (GObject    *object,
                          guint       property_id,
                          GValue     *value,
                          GParamSpec *pspec)
{
  AstNode *self = AST_NODE (object);
  AstNodePrivate *priv = ast_node_get_instance_private(self); 

  switch (property_id)
    {
    case PROP_TEXT:
      g_value_set_string (value, priv->text);
      break;

    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
ast_node_class_init (AstNodeClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    object_class->set_property = ast_node_set_property;
    object_class->get_property = ast_node_get_property;

    obj_properties[PROP_TEXT] =
        g_param_spec_string ("Text",
                         "Text",
                         "Text of this node.",
                         NULL  /* default value */,
                         G_PARAM_READWRITE);

    g_object_class_install_properties (object_class,
                                     N_PROPERTIES,
                                     obj_properties);
}

static void
ast_node_init (AstNode *self)
{
    AstNodePrivate *priv = ast_node_get_instance_private (self);
    // priv->text = g_strdup ("Dit is een test.");
    /* initialize all public and private members to reasonable default values.
     * They are all automatically initialized to 0 to begin with. */
}