/*!
 * \file
 * \author Stanislav Yaranov <stanislav.yaranov@gmail.com>
 * \date   2016-08-02
 * \brief  Resources set header file.
 */

#ifndef YS_RSRC_SET_MT_H
#define YS_RSRC_SET_MT_H

#include <vector>
#include <memory>
#include <mutex>

namespace ys
{

/*!
 * Class for having a set of resources which need to be used sometimes
 * by different threads.
 * For example, a set of socket resources temporary required
 * when accepting from multiple boost::asio acceptors.
 */
template<class T>
class rsrc_set_mt
{
public:
    /*!
     * Resource type typedef.
     */
    using resource_type = T;

    /*!
     * Resoure pointer typedef.
     */
    using resource_ptr = std::shared_ptr<T>;

    /*!
     * Typedef for resource initializer.
     */
    using initializer_type = std::function<resource_ptr()>;

    /*!
     * Constructor.
     */
    rsrc_set_mt();

    /*!
     * Constructor.
     * \param init Initializer for new resources.
     */
    rsrc_set_mt(initializer_type const& init);

    /*!
     * Take a resource pointer from the set or
     * generate a resource if the set is empty.
     * \return
     */
    resource_ptr
    take();

    /*!
     * Put a resource back to the set.
     * \param r The resource.
     */
    void
    put(resource_ptr r);

    /*!
     * Get a number of resources in the set.
     * \return
     */
    size_t
    size() const;

private:
    /*!
     * Container for resources.
     */
    std::vector<resource_ptr> resources_;

    /*!
     * Auxiliary mutex for making container thread-safe.
     */
    std::mutex m_;

    /*!
     * New resource initializer.
     */
    initializer_type initializer_;
};

} // namespace ys

#include "rsrc_set_mt.tcc"

#endif // YS_RSRC_SET_MT_H

